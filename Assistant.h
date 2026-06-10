// Assistant.h — orchestratore di DECODIUS esposto a QML.
// Gestisce lo stato (Idle/Listening/Thinking/Speaking), parla con Ollama e usa il TTS.
#pragma once
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QString>
#include <QTimer>
#include "OllamaClient.h"
#include "WhisperStt.h"

class QNetworkAccessManager;

#ifdef HAVE_TTS
#include <QTextToSpeech>
#include <QStringList>
#include "PiperTts.h"
#include "XttsTts.h"
#endif

class Assistant : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString lastResponse READ lastResponse NOTIFY lastResponseChanged)
    Q_PROPERTY(bool hasImage READ hasImage NOTIFY hasImageChanged)
    Q_PROPERTY(bool alwaysListening READ alwaysListening NOTIFY alwaysListeningChanged)
    // Nominativo dell'operatore (Call/QRZ): personalizzato al primo avvio.
    Q_PROPERTY(QString callSign READ callSign NOTIFY callSignChanged)
    Q_PROPERTY(bool needsCallSign READ needsCallSign NOTIFY callSignChanged)
    // Pilota automatico: Decodius opera la stazione in autonomia (monitor proattivo).
    Q_PROPERTY(bool autoPilot READ autoPilot NOTIFY autoPilotChanged)
    // Wake-word "Decodius": in ascolto continuo reagisce solo dopo la parola di attivazione.
    Q_PROPERTY(bool wakeWord READ wakeWord NOTIFY wakeWordChanged)
    // Voce TTS scelta (alias: giuseppe/diego/isabella/elsa).
    Q_PROPERTY(QString voice READ voice NOTIFY voiceChanged)
    // Motore voce: "edge" (cloud), "piper" (locale offline), "clone" (la tua voce, XTTS).
    Q_PROPERTY(QString voiceEngine READ voiceEngine NOTIFY voiceEngineChanged)
    // HUD stazione live (stato di Decodium 4, aggiornato in tempo reale).
    Q_PROPERTY(bool stationOnline READ stationOnline NOTIFY stationChanged)
    Q_PROPERTY(QString stationLine1 READ stationLine1 NOTIFY stationChanged)  // modo · banda · freq
    Q_PROPERTY(QString stationLine2 READ stationLine2 NOTIFY stationChanged)  // attività · TX/decodifiche

public:
    enum State { Idle, Listening, Thinking, Speaking };
    Q_ENUM(State)

    explicit Assistant(QObject* parent = nullptr);

    State state() const { return m_state; }
    QString lastResponse() const { return m_lastResponse; }
    bool hasImage() const { return !m_pendingImageB64.isEmpty(); }
    bool alwaysListening() const { return m_alwaysListen; }
    QString callSign() const { return m_callSign; }
    bool needsCallSign() const { return m_callSign.isEmpty(); }
    Q_INVOKABLE void setCallSign(const QString& call);   // salva e applica il nominativo
    bool autoPilot() const { return m_autoPilot; }
    Q_INVOKABLE void setAutoPilot(bool on);   // attiva/disattiva il pilota automatico
    bool wakeWord() const { return m_wakeWord; }
    Q_INVOKABLE void setWakeWord(bool on);    // attiva/disattiva la modalità a mani libere con wake-word
    QString voice() const { return m_voice; }
    Q_INVOKABLE void setVoice(const QString& v);   // cambia voce italiana
    Q_INVOKABLE void cycleVoice();                 // cicla tra le voci disponibili
    QString voiceEngine() const { return m_voiceEngine; }
    Q_INVOKABLE void setVoiceEngine(const QString& e);  // edge | piper | clone
    Q_INVOKABLE void cycleVoiceEngine();                // cicla i motori disponibili
    bool stationOnline() const { return m_stationOnline; }
    QString stationLine1() const { return m_stationLine1; }
    QString stationLine2() const { return m_stationLine2; }

    Q_INVOKABLE void sendText(const QString& text);
    Q_INVOKABLE void setListening(bool on);   // attiva/disattiva l'ascolto continuo
    Q_INVOKABLE void interrupt();             // barge-in: ferma la voce e torna in ascolto
    // Risposta dell'utente al dialog di conferma (es. creazione file).
    Q_INVOKABLE void resolveConfirmation(bool accepted);
    // Multimodale: allega un'immagine (vision) al prossimo messaggio.
    Q_INVOKABLE void attachImage(const QString& fileUrl);
    Q_INVOKABLE void clearImage();

signals:
    void stateChanged();
    void lastResponseChanged();
    void hasImageChanged();
    void alwaysListeningChanged();
    void callSignChanged();
    void autoPilotChanged();
    void wakeWordChanged();
    void voiceChanged();
    void voiceEngineChanged();
    void stationChanged();
    // Inoltrato a QML: uno strumento chiede conferma prima di scrivere.
    void confirmationRequested(const QString& title, const QString& detail);

private:
    void setState(State s);
    void applySystemPrompt();        // sostituisce il nominativo nel prompt e lo invia a Ollama
    QString callConfigPath() const;  // file di config dove salvare il nominativo
    QString m_callSign;              // nominativo operatore (vuoto = primo avvio)
    QString m_sysPromptRaw;          // prompt grezzo (con segnaposto del nominativo)
    void endTurn();   // fine risposta: in always-on riprende l'ascolto, altrimenti Idle
    // Instradamento del riconoscimento vocale, con filtro anti-eco per il barge-in.
    void onSpeechRecognized(const QString& text);
    bool isLikelyEcho(const QString& text) const;   // distingue l'eco di Decodius dalla voce utente
    bool m_voiceBargeIn = true;   // ascolta mentre parla per interrompere a voce
    // Wake-word: in ascolto continuo processa una frase solo se contiene "Decodius"
    // (o se siamo ancora nella finestra di "veglia" dopo l'ultima interazione).
    bool   m_wakeWord = false;
    qint64 m_awakeUntilMs = 0;    // fino a quando accettare frasi senza ripetere la wake-word
    QString m_voice = QStringLiteral("giuseppe");   // voce italiana scelta
    static QString detectLang(const QString& text); // rileva la lingua del testo da pronunciare
    static QString phonetic(const QString& text);    // espande i nominativi in alfabeto fonetico NATO (solo per il TTS)
    QString m_voiceEngine = QStringLiteral("edge");  // motore voce attivo
    void selectBackend();   // sceglie il backend TTS attivo in base a m_voiceEngine

    // HUD stazione live: polling periodico dello stato di Decodium 4.
    void onHudTick();
    QTimer  m_hudTimer;
    QNetworkAccessManager* m_hudNet = nullptr;
    bool    m_stationOnline = false;
    QString m_stationLine1, m_stationLine2;

    // ── Pilota automatico (Fase 3): tick periodico che fa "ragionare e agire" l'LLM
    // sulla banda usando i suoi tool (decodium, dxcluster, memoria, comandi). ──
    void onAutoTick();              // un ciclo del pilota automatico
    QTimer  m_autoTimer;            // cadenza dei tick
    bool    m_autoPilot = false;    // modalità autonoma attiva
    bool    m_inAutoTick = false;   // true mentre è in corso un tick (sopprime l'output se "SILENZIO")

    OllamaClient m_ollama;
    WhisperStt*  m_whisper = nullptr;   // riconoscimento vocale locale (STT)
    State   m_state = Idle;
    QString m_lastResponse;
    QString m_pendingImageB64;   // immagine allegata in attesa di invio (vision)
    bool    m_alwaysListen = false;  // uso a TASTIERA di default: niente ascolto auto
                                     // (il WO Mic non è affidabile per lo STT). Il
                                     // pulsante Mic può comunque attivarlo a richiesta.

#ifdef HAVE_TTS
    // Segmentazione per-frase: estrae le frasi complete dal testo in streaming
    // e le pronuncia in coda (una alla volta), senza aspettare la fine.
    void enqueueSentences(bool flushRemainder);   // accoda le frasi pronte
    void speakNext();                             // avvia la prossima se il TTS è libero
    // Backend vocale astratto: Piper (neural) se disponibile, altrimenti QTextToSpeech.
    bool ttsBusy() const;
    void ttsSay(const QString& text);
    void ttsStop();

    XttsTts*       m_xtts = nullptr;    // client del server voce edge (cloud)
    bool           m_xttsReady = false; // server edge pronto
    bool           m_useXtts = false;   // edge attivo per la risposta corrente
    XttsTts*       m_xttsClone = nullptr; // voce clonata (XTTS, server locale)
    bool           m_useClone = false;    // clone attivo per la risposta corrente
    bool           m_xttsPausedForImage = false; // XTTS spento per liberare VRAM (query vision)
    PiperTts*      m_piper = nullptr;   // sintesi neurale Piper (fallback)
    bool           m_usePiper = false;
    QTextToSpeech* m_tts = nullptr;  // fallback col motore migliore (winrt)
    QStringList m_ttsQueue;          // blocchi in attesa di essere pronunciati
    QString     m_ttsPending;        // testo non ancora segmentato in frasi
    QString     m_ttsChunk;          // frasi corte in accumulo (< soglia minima)
    bool        m_streaming = false; // true mentre arrivano token da Ollama
#endif
};
