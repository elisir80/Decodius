// Assistant.cpp
#include "Assistant.h"
#include <QLocale>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QStandardPaths>
#include <QUrl>
#include <QTimer>
#include <QProcess>
#include <QProcessEnvironment>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

static const char* kSystemPrompt =
    "Ti chiami Decodius. Sei l'assistente personale di Martino, radioamatore (IU8LMC) "
    "e sviluppatore. Giri in locale sul suo PC, senza cloud. "
    "Rispondi SEMPRE in italiano, in modo conciso e diretto: le risposte vengono lette ad alta voce. "
    "Niente elenchi o markdown quando parli: frasi brevi e naturali, una o due quando bastano. "
    "Tono pratico e cordiale. Se non sai qualcosa, dillo con onestà.";

static QString decodiusResourcePath(const QString& relativePath) {
    const QString appDir = QCoreApplication::applicationDirPath();
    QStringList bases{appDir};
#if defined(Q_OS_MACOS)
    bases << QDir(appDir).absoluteFilePath(QStringLiteral("../Resources"));
#endif
    for (const QString& base : bases) {
        const QString path = QDir(base).absoluteFilePath(relativePath);
        if (QFileInfo::exists(path))
            return path;
    }
    return QDir(appDir).absoluteFilePath(relativePath);
}

Assistant::Assistant(QObject* parent) : QObject(parent) {
    m_availableModels << m_ollama.model();
    m_modelStatus = QStringLiteral("Modello attivo: %1").arg(m_ollama.model());

    // Persona/competenza caricata da file (decodius_system.txt, esperto radioamatori),
    // così è aggiornabile senza ricompilare; fallback al prompt minimo integrato.
    m_sysPromptRaw = QString::fromUtf8(kSystemPrompt);
    QFile pf(decodiusResourcePath(QStringLiteral("decodius_system.txt")));
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
    const QString wbase = decodiusResourcePath(QStringLiteral("whisper"));
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
    const QString ebase = decodiusResourcePath(QStringLiteral("edge"));
    // Python per la voce edge: preferisci quello PORTATILE bundlato (pyedge, per
    // l'installer pubblico), poi fallback a un Python di sistema (sviluppo).
    QString epy = decodiusResourcePath(QStringLiteral("pyedge/pythonw.exe"));
    if (!QFileInfo::exists(epy)) epy = decodiusResourcePath(QStringLiteral("pyedge/python.exe"));
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
    const QString base = decodiusResourcePath(QStringLiteral("piper"));
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

QString Assistant::findOllamaExecutable() const {
    QString exe = QStandardPaths::findExecutable(QStringLiteral("ollama"));
    if (!exe.isEmpty()) return exe;
    exe = QStandardPaths::findExecutable(QStringLiteral("ollama.exe"));
    if (!exe.isEmpty()) return exe;

    QStringList candidates;
#if defined(Q_OS_WIN)
    const QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    const QString localAppData = env.value(QStringLiteral("LOCALAPPDATA"));
    const QString programFiles = env.value(QStringLiteral("ProgramFiles"));
    const QString programFilesX86 = env.value(QStringLiteral("ProgramFiles(x86)"));
    if (!localAppData.isEmpty())
        candidates << localAppData + QStringLiteral("/Programs/Ollama/ollama.exe");
    if (!programFiles.isEmpty())
        candidates << programFiles + QStringLiteral("/Ollama/ollama.exe");
    if (!programFilesX86.isEmpty())
        candidates << programFilesX86 + QStringLiteral("/Ollama/ollama.exe");
#elif defined(Q_OS_MACOS)
    const QString home = QDir::homePath();
    candidates << QStringLiteral("/Applications/Ollama.app/Contents/Resources/ollama")
               << home + QStringLiteral("/Applications/Ollama.app/Contents/Resources/ollama")
               << QStringLiteral("/opt/homebrew/bin/ollama")
               << QStringLiteral("/usr/local/bin/ollama");
#else
    candidates << QStringLiteral("/usr/local/bin/ollama")
               << QStringLiteral("/usr/bin/ollama")
               << QStringLiteral("/bin/ollama");
#endif

    for (const QString& candidate : candidates) {
        const QFileInfo info(candidate);
        if (info.exists() && info.isFile())
            return info.absoluteFilePath();
    }
    return {};
}

bool Assistant::hasOllamaInstall() const {
    if (!findOllamaExecutable().isEmpty()) return true;
#if defined(Q_OS_MACOS)
    const QString home = QDir::homePath();
    return QFileInfo::exists(QStringLiteral("/Applications/Ollama.app"))
        || QFileInfo::exists(home + QStringLiteral("/Applications/Ollama.app"));
#else
    return false;
#endif
}

QString Assistant::setupScriptPath() const {
    const QString appDir = QCoreApplication::applicationDirPath();
    const QString currentDir = QDir::currentPath();
    const QStringList candidates = {
        appDir + QStringLiteral("/setup_cervello.ps1"),
        decodiusResourcePath(QStringLiteral("setup_cervello.ps1")),
        currentDir + QStringLiteral("/setup_cervello.ps1"),
        QDir(appDir).absoluteFilePath(QStringLiteral("../setup_cervello.ps1"))
    };
    for (const QString& candidate : candidates) {
        const QFileInfo info(candidate);
        if (info.exists() && info.isFile())
            return info.absoluteFilePath();
    }
    return {};
}

QString Assistant::ollamaInstallHint() const {
#if defined(Q_OS_WIN)
    return QStringLiteral("Windows: usa Configura automaticamente oppure installa Ollama dal sito ufficiale.");
#elif defined(Q_OS_MACOS)
    return QStringLiteral("macOS: scarica Ollama.dmg dal sito ufficiale, trascina Ollama in Applicazioni e avvia Ollama.");
#else
    return QStringLiteral("Linux: installa con il comando ufficiale: curl -fsSL https://ollama.com/install.sh | sh");
#endif
}

void Assistant::updateOllamaPrerequisite(bool installed, bool reachable, const QString& status) {
    const bool changed = (m_ollamaInstalled != installed)
        || (m_ollamaReachable != reachable)
        || (m_ollamaStatusText != status);
    m_ollamaInstalled = installed;
    m_ollamaReachable = reachable;
    m_ollamaStatusText = status;
    if (changed)
        emit ollamaPrerequisiteChanged();
}

void Assistant::requestOllamaPrompt(bool userRequested) {
    if (!userRequested && m_ollamaStartupPromptShown)
        return;
    m_ollamaStartupPromptShown = true;

#if defined(Q_OS_WIN)
    const bool canRunSetup = !setupScriptPath().isEmpty();
#else
    const bool canRunSetup = false;
#endif
    const bool canStart = m_ollamaInstalled;
    const QString title = m_ollamaInstalled
        ? QStringLiteral("Ollama non risponde")
        : QStringLiteral("Ollama richiesto");
    const QString summary = m_ollamaInstalled
        ? QStringLiteral("Decodius ha trovato Ollama, ma il servizio locale non risponde su 127.0.0.1:11434.")
        : QStringLiteral("Decodius usa Ollama come cervello: senza Ollama installato non puo' generare risposte.");
    const QString detail = canRunSetup
        ? QStringLiteral("Puoi avviare la configurazione automatica: installa o prepara Ollama, avvia il servizio e configura il modello richiesto.")
        : ollamaInstallHint() + QStringLiteral("\n\nDopo l'installazione torna qui e premi Ricontrolla.");

    emit ollamaSetupPromptRequested(title, summary, detail, canStart, canRunSetup);
}

void Assistant::checkOllamaPrerequisite(bool userRequested) {
    const bool installedOnDisk = hasOllamaInstall();
    updateOllamaPrerequisite(installedOnDisk, m_ollamaReachable,
                             QStringLiteral("Verifica di Ollama in corso..."));

    QNetworkRequest req{QUrl(QStringLiteral("http://127.0.0.1:11434/api/version"))};
    QNetworkReply* reply = m_modelsNet.get(req);
    QTimer::singleShot(2500, reply, [reply]() {
        if (reply->isRunning())
            reply->abort();
    });

    connect(reply, &QNetworkReply::finished, this, [this, reply, userRequested, installedOnDisk]() {
        const QNetworkReply::NetworkError err = reply->error();
        const QString errText = reply->errorString();
        reply->deleteLater();

        const bool reachable = (err == QNetworkReply::NoError);
        const bool installed = installedOnDisk || reachable;
        const QString status = reachable
            ? QStringLiteral("Ollama attivo e raggiungibile.")
            : (installed
                ? QStringLiteral("Ollama installato, ma il servizio non risponde: %1").arg(errText)
                : QStringLiteral("Ollama non trovato nel sistema."));

        updateOllamaPrerequisite(installed, reachable, status);
        if (!reachable)
            requestOllamaPrompt(userRequested);
    });
}

void Assistant::openOllamaDownload() {
#if defined(Q_OS_WIN)
    const QUrl url(QStringLiteral("https://ollama.com/download/windows"));
#elif defined(Q_OS_MACOS)
    const QUrl url(QStringLiteral("https://ollama.com/download/mac"));
#else
    const QUrl url(QStringLiteral("https://ollama.com/download/linux"));
#endif
    QDesktopServices::openUrl(url);
}

bool Assistant::runOllamaSetup() {
#if !defined(Q_OS_WIN)
    openOllamaDownload();
    return false;
#else
    const QString script = setupScriptPath();
    if (script.isEmpty()) {
        openOllamaDownload();
        return false;
    }

    const bool ok = QProcess::startDetached(
        QStringLiteral("powershell.exe"),
        {QStringLiteral("-ExecutionPolicy"), QStringLiteral("Bypass"),
         QStringLiteral("-File"), QDir::toNativeSeparators(script)});
    if (!ok) {
        openOllamaDownload();
        return false;
    }

    m_ollamaSetupRunning = true;
    m_ollamaStatusText = QStringLiteral("Configurazione Ollama avviata in una finestra separata.");
    emit ollamaPrerequisiteChanged();
    QTimer::singleShot(30000, this, [this]() {
        m_ollamaSetupRunning = false;
        emit ollamaPrerequisiteChanged();
        checkOllamaPrerequisite(false);
    });
    return true;
#endif
}

bool Assistant::startOllamaService() {
    const QString exe = findOllamaExecutable();
    bool ok = false;
    if (!exe.isEmpty()) {
        ok = QProcess::startDetached(exe, {QStringLiteral("serve")});
    }
#if defined(Q_OS_MACOS)
    if (!ok) {
        const QString home = QDir::homePath();
        if (QFileInfo::exists(QStringLiteral("/Applications/Ollama.app")))
            ok = QProcess::startDetached(QStringLiteral("open"), {QStringLiteral("-a"), QStringLiteral("Ollama")});
        else if (QFileInfo::exists(home + QStringLiteral("/Applications/Ollama.app")))
            ok = QProcess::startDetached(QStringLiteral("open"), {home + QStringLiteral("/Applications/Ollama.app")});
    }
#endif
    if (ok) {
        m_ollamaStatusText = QStringLiteral("Avvio di Ollama richiesto. Ricontrollo tra pochi secondi...");
        emit ollamaPrerequisiteChanged();
        QTimer::singleShot(2500, this, [this]() { checkOllamaPrerequisite(false); });
        QTimer::singleShot(6500, this, [this]() { checkOllamaPrerequisite(false); });
    } else {
        openOllamaDownload();
    }
    return ok;
}

void Assistant::refreshModels() {
    if (m_modelsLoading) return;

    m_modelsLoading = true;
    m_modelStatus = QStringLiteral("Lettura modelli da Ollama...");
    emit modelsLoadingChanged();
    emit modelStatusChanged();

    QNetworkRequest req{QUrl(QStringLiteral("http://localhost:11434/api/tags"))};
    QNetworkReply* reply = m_modelsNet.get(req);
    QTimer::singleShot(6000, reply, [reply]() {
        if (reply->isRunning())
            reply->abort();
    });

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        const QNetworkReply::NetworkError err = reply->error();
        const QByteArray raw = reply->readAll();
        const QString errText = reply->errorString();
        reply->deleteLater();

        QStringList next = m_availableModels;
        if (!next.contains(m_ollama.model()))
            next.prepend(m_ollama.model());

        if (err == QNetworkReply::NoError) {
            QJsonParseError parseError;
            const QJsonObject root = QJsonDocument::fromJson(raw, &parseError).object();
            if (parseError.error == QJsonParseError::NoError) {
                next.clear();
                const QJsonArray models = root.value(QStringLiteral("models")).toArray();
                for (const QJsonValue& value : models) {
                    const QJsonObject obj = value.toObject();
                    QString name = obj.value(QStringLiteral("name")).toString().trimmed();
                    if (name.isEmpty())
                        name = obj.value(QStringLiteral("model")).toString().trimmed();
                    if (!name.isEmpty() && !next.contains(name))
                        next << name;
                }
                std::sort(next.begin(), next.end(), [](const QString& a, const QString& b) {
                    return QString::compare(a, b, Qt::CaseInsensitive) < 0;
                });
                if (!next.contains(m_ollama.model()))
                    next.prepend(m_ollama.model());
                m_modelStatus = next.isEmpty()
                    ? QStringLiteral("Nessun modello trovato in Ollama.")
                    : QStringLiteral("%1 modelli disponibili.").arg(next.size());
            } else {
                m_modelStatus = QStringLiteral("Risposta Ollama non valida.");
            }
        } else {
            m_modelStatus = QStringLiteral("Ollama non raggiungibile: %1").arg(errText);
        }

        if (next != m_availableModels) {
            m_availableModels = next;
            emit availableModelsChanged();
        }
        m_modelsLoading = false;
        emit modelsLoadingChanged();
        emit modelStatusChanged();
    });
}

void Assistant::setCurrentModel(const QString& model) {
    const QString next = model.trimmed();
    if (next.isEmpty() || next == m_ollama.model()) return;

    m_ollama.cancel();
    m_ollama.setModel(next);
    if (!m_availableModels.contains(next)) {
        m_availableModels.prepend(next);
        emit availableModelsChanged();
    }
    m_modelStatus = QStringLiteral("Modello attivo: %1").arg(next);
    emit currentModelChanged();
    emit modelStatusChanged();
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

// Sostituisce nel prompt il nominativo/nome dell'autore con quello dell'utente.
void Assistant::applySystemPrompt() {
    QString p = m_sysPromptRaw;
    if (!m_callSign.isEmpty()) {
        p.replace(QStringLiteral("IU8LMC"), m_callSign);
        p.replace(QStringLiteral("Martino"), m_callSign);
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
