// WhisperStt.h — riconoscimento vocale locale (faster-whisper) via server Python.
// Avvia whisper_server.py, attende /ready; listen() registra dal microfono finché
// parli e restituisce il testo trascritto (segnale recognized).
#pragma once
#include <QObject>
#include <QString>

class QProcess;
class QNetworkAccessManager;
class QNetworkReply;
class QTimer;

class WhisperStt : public QObject {
    Q_OBJECT
public:
    WhisperStt(const QString& pythonExe, const QString& serverScript,
               const QString& model = QStringLiteral("small"),
               int port = 5068, QObject* parent = nullptr);
    ~WhisperStt() override;

    bool isAvailable() const { return m_available; }   // python + script presenti
    bool isReady() const { return m_ready; }
    bool isListening() const { return m_listening; }

    void start();        // lancia il server (o riusa quello attivo) e attende /ready
    void listen();       // registra e trascrive: emette recognized(text)
    void cancel();       // annulla l'ascolto in corso

signals:
    void recognized(const QString& text);
    void ready();
    void listeningChanged();

private:
    void launchServer();
    void beginReadyPolling();
    void pollReady();

    QString m_python, m_script, m_model, m_host;
    int  m_port;
    bool m_available = false;
    bool m_ready = false;
    bool m_listening = false;
    int  m_pollTries = 0;

    QProcess*              m_server = nullptr;
    QNetworkAccessManager* m_net = nullptr;
    QNetworkReply*         m_listenReply = nullptr;
    QTimer*                m_pollTimer = nullptr;
};
