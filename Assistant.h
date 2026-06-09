// Assistant.h — orchestratore di DECODIUS esposto a QML.
// Gestisce lo stato (Idle/Listening/Thinking/Speaking), parla con Ollama e usa il TTS.
#pragma once
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QString>
#include "OllamaClient.h"
#include "WhisperStt.h"

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

    XttsTts*       m_xtts = nullptr;    // sintesi neurale XTTS v2 (preferita assoluta)
    bool           m_xttsReady = false; // server XTTS pronto
    bool           m_useXtts = false;   // XTTS attivo per la risposta corrente
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
