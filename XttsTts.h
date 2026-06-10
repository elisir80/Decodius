// XttsTts.h — backend vocale neurale (Coqui XTTS v2) via server locale.
// Avvia server.py come processo figlio, attende /ready, e per ogni blocco di
// testo fa POST /tts -> WAV, riprodotto con QMediaPlayer. Stessa interfaccia di
// PiperTts (isBusy/say/stop/finished) per incastrarsi negli helper di Assistant.
#pragma once
#include <QObject>
#include <QString>

class QProcess;
class QMediaPlayer;
class QAudioOutput;
class QNetworkAccessManager;
class QNetworkReply;
class QTimer;

class XttsTts : public QObject {
    Q_OBJECT
public:
    // pythonExe: venv\Scripts\python.exe ; serverScript: server.py ;
    // speaker: nome speaker integrato ; speakerWav: clip di riferimento (priorità)
    XttsTts(const QString& pythonExe, const QString& serverScript,
            const QString& speaker, const QString& speakerWav,
            int port = 5067, QObject* parent = nullptr);
    ~XttsTts() override;

    bool isAvailable() const { return m_available; }   // python + script presenti
    bool isReady() const { return m_ready; }           // server caricato e pronto
    bool isBusy() const { return m_busy; }

    void start();                    // lancia il server e avvia il polling /ready
    void stopServer();               // spegne il server (libera VRAM); start() lo riavvia
    void say(const QString& text);   // sintetizza e riproduce un blocco
    void stop();                     // interrompe richiesta e riproduzione correnti
    void setVoice(const QString& v) { m_voice = v; }  // alias/nome voce edge (vuoto = default)
    void setLang(const QString& l)  { m_lang = l; }   // lingua per la voce (vuoto = default it)

signals:
    void finished();                 // riproduzione del blocco terminata (idle)
    void ready();                    // server diventato /ready

private:
    void launchServer();        // avvia server.py come processo figlio
    void beginReadyPolling();   // avvia il polling di /ready
    void pollReady();
    void startPlayback(const QString& wav);
    void onPlaybackFinished();

    QString m_python, m_script, m_speaker, m_speakerWav, m_host;
    QString m_voice, m_lang;     // override voce/lingua inviati al server TTS
    int     m_port;
    bool    m_available = false;
    bool    m_ready = false;
    bool    m_busy = false;
    bool    m_stopping = false;
    int     m_counter = 0;
    int     m_pollTries = 0;
    QString m_curWav;

    QProcess*              m_server = nullptr;
    QNetworkAccessManager* m_net = nullptr;
    QNetworkReply*         m_ttsReply = nullptr;
    QTimer*                m_pollTimer = nullptr;
    QMediaPlayer*          m_player = nullptr;
    QAudioOutput*          m_audio = nullptr;
};
