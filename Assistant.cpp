// Assistant.cpp
#include "Assistant.h"
#include <QLocale>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include <QUrl>
#include <QTimer>

static const char* kSystemPrompt =
    "Ti chiami Decodius. Sei l'assistente personale di Martino, radioamatore (IU8LMC) "
    "e sviluppatore. Giri in locale sul suo PC, senza cloud. "
    "Rispondi SEMPRE in italiano, in modo conciso e diretto: le risposte vengono lette ad alta voce. "
    "Niente elenchi o markdown quando parli: frasi brevi e naturali, una o due quando bastano. "
    "Tono pratico e cordiale. Se non sai qualcosa, dillo con onestà.";

Assistant::Assistant(QObject* parent) : QObject(parent) {
    // Persona/competenza caricata da file (decodius_system.txt, esperto radioamatori),
    // così è aggiornabile senza ricompilare; fallback al prompt minimo integrato.
    m_sysPromptRaw = QString::fromUtf8(kSystemPrompt);
    QFile pf(QCoreApplication::applicationDirPath() + QStringLiteral("/decodius_system.txt"));
    if (pf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        const QString loaded = QString::fromUtf8(pf.readAll()).trimmed();
        if (!loaded.isEmpty()) m_sysPromptRaw = loaded;
        pf.close();
    }
    // Nominativo salvato (Call/QRZ). Se assente -> primo avvio: la UI lo chiederà.
    QFile cf(callConfigPath());
    if (cf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_callSign = QString::fromUtf8(cf.readAll()).trimmed().toUpper();
        cf.close();
    }
    applySystemPrompt();   // invia il prompt a Ollama (col nominativo se presente)

    // Streaming: ogni token appena generato viene appeso e mostrato subito.
    connect(&m_ollama, &OllamaClient::tokenReceived, this, [this](const QString& chunk) {
        m_lastResponse += chunk;
        emit lastResponseChanged();
        if (m_state != Speaking) setState(Speaking);   // "RISPONDO" mentre scrive
#ifdef HAVE_TTS
        m_ttsPending += chunk;
        enqueueSentences(false);   // accoda le frasi già complete
        speakNext();               // e parte se il TTS è libero
#endif
    });

    connect(&m_ollama, &OllamaClient::responseReady, this, [this](const QString& text) {
        m_lastResponse = text;   // versione finale ripulita (trim)
        emit lastResponseChanged();
#ifdef HAVE_TTS
        m_streaming = false;
        enqueueSentences(true);    // svuota l'ultima coda di testo
        speakNext();               // se non c'è nulla da dire, porta a Idle
        if (m_xttsPausedForImage) { // riaccendo XTTS dopo la query vision
            m_xttsPausedForImage = false;
            if (m_xtts) m_xtts->start();
        }
#else
        endTurn();                 // senza TTS: fine turno (riascolta se always-on)
#endif
    });

    // Inoltro a QML la richiesta di conferma di uno strumento in scrittura.
    connect(&m_ollama, &OllamaClient::confirmationRequested, this,
            [this](const QString& title, const QString& detail) {
        emit confirmationRequested(title, detail);
    });

    connect(&m_ollama, &OllamaClient::errorOccurred, this, [this](const QString& msg) {
        m_lastResponse = "Errore di connessione a Ollama: " + msg;
        emit lastResponseChanged();
#ifdef HAVE_TTS
        m_streaming = false;
        m_ttsQueue.clear();
        m_ttsPending.clear();
        m_ttsChunk.clear();
        ttsStop();
        if (m_xttsPausedForImage) {  // riaccendo XTTS anche in caso di errore
            m_xttsPausedForImage = false;
            if (m_xtts) m_xtts->start();
        }
#endif
        endTurn();
    });

    // ── Voce-in: riconoscimento vocale locale (Whisper su CPU, niente VRAM) ──
    const QString wbase = QCoreApplication::applicationDirPath() + QStringLiteral("/whisper");
    m_whisper = new WhisperStt(wbase + QStringLiteral("/venv/Scripts/python.exe"),
                               wbase + QStringLiteral("/whisper_server.py"),
                               QStringLiteral("small"), 5068, this);
    if (m_whisper->isAvailable()) {
        connect(m_whisper, &WhisperStt::listeningChanged, this, [this]() {
            if (m_whisper->isListening()) setState(Listening);
        });
        connect(m_whisper, &WhisperStt::recognized, this, [this](const QString& text) {
            // Ciclo audio STABILE (niente barge-in vocale: causava use-after-free in
            // Qt6Core tenendo il mic acceso durante il parlato). Interruzione: clic.
            if (!text.isEmpty()) sendText(text);
            else endTurn();
        });
        // Appena il modello è pronto, in modalità always-on parte subito l'ascolto.
        connect(m_whisper, &WhisperStt::ready, this, [this]() {
            if (m_alwaysListen) m_whisper->listen();
        });
        m_whisper->start();   // carica il modello in background
    }

#ifdef HAVE_TTS
    const QString appDir = QCoreApplication::applicationDirPath();

    // Voce edge-tts "it-IT-GiuseppeNeural" (Microsoft, CLOUD gratis senza API):
    // dizione italiana eccellente e molto naturale, ~1-2s/frase. Scelta per il miglior
    // realismo gratuito (Chatterbox locale troppo lento, Chatterbox cloud a pagamento).
    // Server edge_server.py (POST /tts -> MP3), Python 3.14 con edge-tts. Fallback:
    // Piper -> QTextToSpeech. (Kokoro/XTTS/Chatterbox restano disponibili come alternative.)
    const QString ebase = appDir + QStringLiteral("/edge");
    // Python per la voce edge: preferisci quello PORTATILE bundlato (pyedge, per
    // l'installer pubblico), poi fallback a un Python di sistema (sviluppo).
    QString epy = appDir + QStringLiteral("/pyedge/pythonw.exe");
    if (!QFileInfo::exists(epy)) epy = appDir + QStringLiteral("/pyedge/python.exe");
    if (!QFileInfo::exists(epy)) epy = QStringLiteral("C:/Python314/pythonw.exe");
    if (!QFileInfo::exists(epy)) epy = QStringLiteral("C:/Python314/python.exe");
    m_xtts = new XttsTts(epy,
                         ebase + QStringLiteral("/edge_server.py"),
                         QStringLiteral("it-IT-GiuseppeNeural"),
                         QString(), 5069, this);
    if (m_xtts->isAvailable()) {
        connect(m_xtts, &XttsTts::finished, this, [this]() { speakNext(); });
        connect(m_xtts, &XttsTts::ready, this, [this]() { m_xttsReady = true; });
        m_xtts->start();
    }

    // Fallback voce: Piper (CPU, cartella "piper/").
    const QString base = appDir + QStringLiteral("/piper");
    m_piper = new PiperTts(base + QStringLiteral("/piper.exe"),
                           base + QStringLiteral("/voices/it_IT-paola-medium.onnx"),
                           this);
    m_usePiper = m_piper->isAvailable();

    if (m_usePiper) {
        // A fine riproduzione di un blocco, passo al successivo.
        connect(m_piper, &PiperTts::finished, this, [this]() { speakNext(); });
    } else {
        // 2) Fallback: QTextToSpeech col motore migliore (WinRT/OneCore -> SAPI).
        const QStringList engines = QTextToSpeech::availableEngines();
        const QString engine = engines.contains(QStringLiteral("winrt"))
            ? QStringLiteral("winrt") : QString();
        m_tts = engine.isEmpty() ? new QTextToSpeech(this)
                                 : new QTextToSpeech(engine, this);
        m_tts->setLocale(QLocale(QLocale::Italian, QLocale::Italy));

        const QList<QVoice> voices = m_tts->availableVoices();
        QVoice chosen;
        for (const QVoice& v : voices)
            if (v.name().contains(QStringLiteral("Cosimo"), Qt::CaseInsensitive)) { chosen = v; break; }
        if (chosen.name().isEmpty() && !voices.isEmpty())
            chosen = voices.first();
        if (!chosen.name().isEmpty())
            m_tts->setVoice(chosen);

        m_tts->setVolume(1.0);
        m_tts->setRate(-0.1);
        m_tts->setPitch(0.0);

        connect(m_tts, &QTextToSpeech::stateChanged, this, [this](QTextToSpeech::State s) {
            if (s == QTextToSpeech::Ready) speakNext();
        });
    }
#endif
}

#ifdef HAVE_TTS
// Backend vocale a cascata: XTTS (se attivo) -> Piper -> QTextToSpeech.
// m_useXtts viene "congelato" a inizio risposta (vedi sendText) per non
// cambiare voce a metà di una risposta.
bool Assistant::ttsBusy() const {
    if (m_useXtts) return m_xtts->isBusy();
    if (m_usePiper) return m_piper->isBusy();
    return m_tts && (m_tts->state() == QTextToSpeech::Speaking ||
                     m_tts->state() == QTextToSpeech::Paused);
}
void Assistant::ttsSay(const QString& text) {
    if (m_useXtts) m_xtts->say(text);
    else if (m_usePiper) m_piper->say(text);
    else if (m_tts) m_tts->say(text);
}
void Assistant::ttsStop() {
    if (m_xtts) m_xtts->stop();
    if (m_piper) m_piper->stop();
    if (m_tts) m_tts->stop();
}
#endif

#ifdef HAVE_TTS
// Lunghezza minima di un blocco da pronunciare: le frasi più corte vengono
// unite alla successiva, così la voce non suona spezzettata.
static constexpr int kMinTtsLen = 18;   // basso: prima porzione parlata quasi subito (GPU regge)

// Ripulisce il markdown da una frase prima di darla al TTS: la voce non deve
// leggere asterischi, backtick, cancelletti o trattini di elenco. Il testo a
// schermo resta integro (e viene renderizzato come markdown in QML).
static QString cleanForSpeech(QString s) {
    // link [testo](url) -> testo
    s.replace(QRegularExpression(QStringLiteral("\\[([^\\]]+)\\]\\([^)]*\\)")),
              QStringLiteral("\\1"));
    // marcatori a inizio riga: elenco (- * +), numerato (1.), heading (#), citazione (>)
    s.replace(QRegularExpression(QStringLiteral("(?m)^\\s*([-*+]|\\d+\\.)\\s+")), QString());
    s.replace(QRegularExpression(QStringLiteral("(?m)^\\s*#+\\s*")), QString());
    s.replace(QRegularExpression(QStringLiteral("(?m)^\\s*>\\s*")), QString());
    // LaTeX: \text{MHz} -> MHz, \mathrm{...} -> ..., poi via dollari e backslash
    s.replace(QRegularExpression(QStringLiteral("\\\\[a-zA-Z]+\\{([^}]*)\\}")), QStringLiteral("\\1"));
    // enfasi/codice/LaTeX: rimuovo asterischi, backtick, cancelletti, dollari, backslash
    s.remove(QRegularExpression(QStringLiteral("[*`#$\\\\]")));
    // collassa spazi/tab multipli
    s.replace(QRegularExpression(QStringLiteral("[ \\t]{2,}")), QStringLiteral(" "));
    return s.trimmed();
}

void Assistant::enqueueSentences(bool flushRemainder) {
    // Confini di frase E di inciso (virgola, ; :): con Kokoro su GPU (sintesi ~0,15s)
    // la voce parte al primo inciso (~0,6s) e resta fluida -> sincrona col testo.
    static const QString enders = QStringLiteral(".!?…,;:\n");
    int start = 0;
    for (int i = 0; i < m_ttsPending.size(); ++i) {
        const QChar c = m_ttsPending.at(i);
        if (!enders.contains(c)) continue;
        // Confine valido solo se newline o seguito da spazio: evita di spezzare
        // numeri/abbreviazioni (es. "11.434") e attende il token successivo.
        const bool newline = (c == QLatin1Char('\n'));
        const bool spaceAfter = (i + 1 < m_ttsPending.size()) && m_ttsPending.at(i + 1).isSpace();
        if (!newline && !spaceAfter) continue;

        const QString sentence = cleanForSpeech(m_ttsPending.mid(start, i + 1 - start));
        start = i + 1;
        if (sentence.isEmpty()) continue;

        // Accumula: accodo solo quando il blocco raggiunge la soglia minima.
        if (!m_ttsChunk.isEmpty()) m_ttsChunk += QLatin1Char(' ');
        m_ttsChunk += sentence;
        if (m_ttsChunk.size() >= kMinTtsLen) {
            m_ttsQueue << m_ttsChunk;
            m_ttsChunk.clear();
        }
    }
    m_ttsPending = m_ttsPending.mid(start);

    if (flushRemainder) {
        // Fine risposta: unisco l'ultimo spezzone e svuoto comunque l'accumulo,
        // anche se sotto soglia (è l'ultima cosa da dire).
        const QString tail = cleanForSpeech(m_ttsPending);
        if (!tail.isEmpty()) {
            if (!m_ttsChunk.isEmpty()) m_ttsChunk += QLatin1Char(' ');
            m_ttsChunk += tail;
        }
        m_ttsPending.clear();
        if (!m_ttsChunk.isEmpty()) {
            m_ttsQueue << m_ttsChunk;
            m_ttsChunk.clear();
        }
    }
}

void Assistant::speakNext() {
    // Non interrompere un blocco in corso.
    if (ttsBusy()) return;
    if (!m_ttsQueue.isEmpty()) {
        ttsSay(m_ttsQueue.takeFirst());
        return;
    }
    // Coda vuota: se lo stream è finito, l'assistente ha smesso di parlare.
    if (!m_streaming && m_state == Speaking) endTurn();
}
#endif

void Assistant::sendText(const QString& text) {
    QString t = text.trimmed();
    const bool hasImg = !m_pendingImageB64.isEmpty();
    if (t.isEmpty() && !hasImg) return;
    if (t.isEmpty()) t = QStringLiteral("Descrivi questa immagine.");  // query solo-immagine
    // Se Decodius sta già elaborando o parlando, annullo PRIMA in modo silenzioso
    // (niente errore spurio): così una nuova istruzione interrompe e prende il posto.
    m_ollama.cancel();
    m_lastResponse.clear();          // svuota: il testo comparirà token per token
    emit lastResponseChanged();
#ifdef HAVE_TTS
    m_streaming = true;              // prima dello stop, così non scatta Idle
    // SOLO Kokoro: se il server voce è disponibile lo uso sempre (mai Piper/voce di
    // sistema, che suonerebbero diversi). Il server è persistente, quindi pronto.
    m_useXtts = (m_xtts && m_xtts->isAvailable());
    m_ttsQueue.clear();
    m_ttsPending.clear();
    m_ttsChunk.clear();
    ttsStop();                        // zittisci la risposta precedente
#endif
    if (hasImg) {                     // allega l'immagine (vision) a questo messaggio
        m_ollama.setPendingImage(m_pendingImageB64);
        m_pendingImageB64.clear();
        emit hasImageChanged();
    }
    setState(Thinking);
    m_ollama.ask(t);
}

void Assistant::attachImage(const QString& fileUrl) {
    QString path = fileUrl;
    if (path.startsWith(QStringLiteral("file:"))) path = QUrl(fileUrl).toLocalFile();
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) return;
    const QByteArray data = f.readAll();
    f.close();
    if (data.isEmpty()) return;
    m_pendingImageB64 = QString::fromLatin1(data.toBase64());
    emit hasImageChanged();
}

void Assistant::clearImage() {
    if (!m_pendingImageB64.isEmpty()) { m_pendingImageB64.clear(); emit hasImageChanged(); }
}

void Assistant::interrupt() {
    // Barge-in: l'utente vuole intervenire mentre Decodius parla o elabora.
    m_ollama.cancel();                 // ferma la generazione in corso (silenzioso)
#ifdef HAVE_TTS
    m_streaming = false;
    m_ttsQueue.clear();
    m_ttsPending.clear();
    m_ttsChunk.clear();
    ttsStop();                         // zittisci la voce in corso
#endif
    // Torna subito in ascolto (in always-on) così puoi parlare immediatamente.
    if (m_alwaysListen && m_whisper && m_whisper->isReady()) {
        setState(Idle);
        if (!m_whisper->isListening()) m_whisper->listen();
    } else {
        setState(Idle);
    }
}

void Assistant::setListening(bool on) {
    // Toggle dell'ascolto continuo (always-on, a mani libere).
    if (m_alwaysListen == on && on) return;
    m_alwaysListen = on;
    emit alwaysListeningChanged();
    if (on) {
        if (m_whisper && m_whisper->isReady() && !m_whisper->isListening()) m_whisper->listen();
        else if (!m_whisper || !m_whisper->isReady()) setState(Listening);
    } else {
        if (m_whisper) m_whisper->cancel();
        if (m_state == Listening) setState(Idle);
    }
}

// Fine di un "turno" (risposta conclusa, errore, o nessuna voce rilevata):
// in modalità always-on torna in ascolto dopo una breve pausa anti-eco
// (per non trascrivere la coda della propria voce); altrimenti va Idle.
void Assistant::endTurn() {
    if (m_alwaysListen && m_whisper && m_whisper->isReady()) {
        setState(Idle);
        QTimer::singleShot(700, this, [this]() {   // anti-eco: lascia spegnere la coda voce
            if (m_alwaysListen && m_state == Idle && !m_whisper->isListening())
                m_whisper->listen();
        });
    } else {
        setState(Idle);
    }
}

void Assistant::resolveConfirmation(bool accepted) {
    m_ollama.resolveConfirmation(accepted);
}

// File dove salvare il nominativo (in una posizione scrivibile anche se l'app è
// installata in Program Files): %APPDATA%/Decodius/call.txt.
QString Assistant::callConfigPath() const {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if (dir.isEmpty()) dir = QCoreApplication::applicationDirPath();
    QDir().mkpath(dir);
    return dir + QStringLiteral("/call.txt");
}

// Memoria persistente letta dal modulo OllamaClient (decodius_memoria.txt).
QString decodiusLeggiMemoria();

// Sostituisce nel prompt il nominativo/nome dell'autore con quello dell'utente,
// e vi innesta la MEMORIA PERSISTENTE così il modello "ricorda" tra le sessioni.
void Assistant::applySystemPrompt() {
    QString p = m_sysPromptRaw;
    if (!m_callSign.isEmpty()) {
        p.replace(QStringLiteral("IU8LMC"), m_callSign);
        p.replace(QStringLiteral("Martino"), m_callSign);
    }
    const QString mem = decodiusLeggiMemoria();
    if (!mem.isEmpty()) {
        p += QStringLiteral("\n\nMEMORIA PERSISTENTE (cose che ricordi dalle sessioni precedenti; "
                            "usala quando pertinente, ma non elencarla a meno che non te lo chieda):\n") + mem;
    }
    m_ollama.setSystemPrompt(p);
}

// Imposta il nominativo (primo avvio o cambio): salva, riapplica il prompt, notifica la UI.
void Assistant::setCallSign(const QString& call) {
    const QString c = call.trimmed().toUpper();
    if (c.isEmpty() || c == m_callSign) return;
    m_callSign = c;
    QFile cf(callConfigPath());
    if (cf.open(QIODevice::WriteOnly | QIODevice::Text)) { cf.write(m_callSign.toUtf8()); cf.close(); }
    applySystemPrompt();
    emit callSignChanged();
}

void Assistant::setState(State s) {
    if (m_state == s) return;
    m_state = s;
    emit stateChanged();
}

// Normalizza in parole minuscole, senza punteggiatura (per il confronto anti-eco).
static QString normWords(const QString& s) {
    QString t = s.toLower();
    t.replace(QRegularExpression(QStringLiteral("[^\\p{L}\\p{N} ]")), QStringLiteral(" "));
    return t.simplified();
}
// Parole con cui l'utente può sempre interrompere (improbabili nell'eco di Decodius).
static bool hasStopWord(const QString& norm) {
    static const char* kStop[] = {"stop","basta","aspetta","fermati","ferma","zitto","taci","ok ok"};
    for (const char* w : kStop) if (norm.contains(QLatin1String(w))) return true;
    return false;
}

// È probabilmente l'eco della voce di Decodius (che il mic risente dagli altoparlanti)?
bool Assistant::isLikelyEcho(const QString& text) const {
    const QString n = normWords(text);
    if (hasStopWord(n)) return false;                 // comando esplicito: non è eco
    const QStringList rec = n.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (rec.size() < 3) return true;                  // frammento troppo corto: tratta come eco
    const QString spoken = normWords(m_lastResponse); // ciò che Decodius sta dicendo
    int fresh = 0;
    for (const QString& w : rec)
        if (w.size() >= 3 && !spoken.contains(w)) ++fresh;
    // Serve un blocco di parole davvero NUOVE per considerarlo barge-in (anti falsi positivi).
    return fresh < 5;
}

// Instrada il testo riconosciuto: durante una risposta filtra l'eco e gestisce il barge-in.
void Assistant::onSpeechRecognized(const QString& text) {
    const QString t = text.trimmed();
    bool responding = m_state == Thinking || m_state == Speaking;
#ifdef HAVE_TTS
    responding = responding || m_streaming || ttsBusy();
#endif
    if (responding) {
        if (t.isEmpty() || isLikelyEcho(t)) {
            // Eco o frammento: ignora e continua ad ascoltare per un eventuale barge-in.
            if (m_voiceBargeIn && m_alwaysListen && m_whisper && m_whisper->isReady() &&
                !m_whisper->isListening())
                m_whisper->listen();
            return;
        }
        interrupt();        // voce reale dell'utente sopra il parlato: interrompi...
        sendText(t);        // ...e processa la nuova richiesta
        return;
    }
    // Turno normale (Decodius non sta parlando).
    if (t.isEmpty()) endTurn();
    else sendText(t);
}
