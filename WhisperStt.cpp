// WhisperStt.cpp
#include "WhisperStt.h"
#include <QProcess>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QFileInfo>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>

static constexpr int kPollIntervalMs = 600;
static constexpr int kPollMaxTries   = 90;     // ~54 s per il caricamento del modello
static constexpr int kListenTimeoutMs = 60000; // copre attesa-voce (30s) + frase (15s) + margine

WhisperStt::WhisperStt(const QString& pythonExe, const QString& serverScript,
                       const QString& model, int port, QObject* parent)
    : QObject(parent), m_python(pythonExe), m_script(serverScript),
      m_model(model), m_port(port) {
    m_host = QStringLiteral("http://127.0.0.1:%1").arg(port);
    m_available = QFileInfo::exists(m_python) && QFileInfo::exists(m_script);
    if (m_available) m_net = new QNetworkAccessManager(this);
}

WhisperStt::~WhisperStt() {
    if (m_server) {
        m_server->terminate();
        if (!m_server->waitForFinished(3000)) m_server->kill();
    }
}

void WhisperStt::start() {
    if (!m_available || m_server || m_pollTimer) return;
    // Riusa un server già attivo, altrimenti lo lancio.
    QNetworkReply* hr = m_net->get(QNetworkRequest(QUrl(m_host + QStringLiteral("/health"))));
    QTimer::singleShot(2500, hr, [hr]() { if (hr->isRunning()) hr->abort(); });
    connect(hr, &QNetworkReply::finished, this, [this, hr]() {
        hr->deleteLater();
        const bool alive = hr->error() == QNetworkReply::NoError &&
            hr->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200;
        if (!alive) launchServer();
        beginReadyPolling();
    });
}

void WhisperStt::launchServer() {
    if (m_server) return;
    m_server = new QProcess(this);
    m_server->setWorkingDirectory(QFileInfo(m_script).absolutePath());
    m_server->start(m_python, { m_script, QStringLiteral("--port"), QString::number(m_port),
                                QStringLiteral("--model"), m_model });
}

void WhisperStt::beginReadyPolling() {
    if (m_pollTimer) return;
    m_pollTries = 0;
    m_pollTimer = new QTimer(this);
    m_pollTimer->setInterval(kPollIntervalMs);
    connect(m_pollTimer, &QTimer::timeout, this, &WhisperStt::pollReady);
    m_pollTimer->start();
    pollReady();
}

void WhisperStt::pollReady() {
    if (m_ready) { m_pollTimer->stop(); return; }
    if (++m_pollTries > kPollMaxTries) { m_pollTimer->stop(); return; }
    QNetworkReply* r = m_net->get(QNetworkRequest(QUrl(m_host + QStringLiteral("/ready"))));
    connect(r, &QNetworkReply::finished, this, [this, r]() {
        r->deleteLater();
        if (!m_ready && r->error() == QNetworkReply::NoError &&
            r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
            m_ready = true;
            if (m_pollTimer) m_pollTimer->stop();
            emit ready();
        }
    });
}

void WhisperStt::listen() {
    if (!m_ready || m_listening) { emit recognized(QString()); return; }
    m_listening = true;
    emit listeningChanged();

    m_listenReply = m_net->get(QNetworkRequest(QUrl(m_host + QStringLiteral("/listen"))));
    QTimer::singleShot(kListenTimeoutMs, m_listenReply, [this]() {
        if (m_listenReply && m_listenReply->isRunning()) m_listenReply->abort();
    });
    connect(m_listenReply, &QNetworkReply::finished, this, [this]() {
        QNetworkReply* r = m_listenReply;
        m_listenReply = nullptr;
        if (!r) return;
        r->deleteLater();
        m_listening = false;
        emit listeningChanged();
        QString text;
        if (r->error() == QNetworkReply::NoError) {
            const QJsonObject o = QJsonDocument::fromJson(r->readAll()).object();
            text = o.value("text").toString().trimmed();
        }
        emit recognized(text);
    });
}

void WhisperStt::cancel() {
    // abort() emette finished() in modo SINCRONO: la lambda di finished() gira
    // rientrante e azzera m_listenReply. Per evitare che la riga successiva operi
    // su un puntatore gia' azzerato (null-deref in Qt6Core), lavoro su una copia
    // locale, azzero PRIMA il membro e scollego la reply cosi' la finished non
    // rientra (niente doppio deleteLater ne' recognized() spurio).
    QNetworkReply* r = m_listenReply;
    m_listenReply = nullptr;
    if (r) {
        r->disconnect(this);
        r->abort();
        r->deleteLater();
    }
    if (m_listening) { m_listening = false; emit listeningChanged(); }
}
