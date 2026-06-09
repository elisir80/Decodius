// XttsTts.cpp
#include "XttsTts.h"
#include <QProcess>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>

static constexpr int kPollIntervalMs = 600;
static constexpr int kPollMaxTries   = 120;   // ~72 s di attesa caricamento modello
static constexpr int kTtsTimeoutMs   = 30000; // timeout sintesi di un blocco

XttsTts::XttsTts(const QString& pythonExe, const QString& serverScript,
                 const QString& speaker, const QString& speakerWav,
                 int port, QObject* parent)
    : QObject(parent), m_python(pythonExe), m_script(serverScript),
      m_speaker(speaker), m_speakerWav(speakerWav), m_port(port) {
    m_host = QStringLiteral("http://127.0.0.1:%1").arg(port);
    m_available = QFileInfo::exists(m_python) && QFileInfo::exists(m_script);
    if (!m_available) return;

    m_net = new QNetworkAccessManager(this);
    m_audio = new QAudioOutput(this);
    m_audio->setVolume(1.0);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_audio);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this,
            [this](QMediaPlayer::MediaStatus s) {
        if (s == QMediaPlayer::EndOfMedia) onPlaybackFinished();
    });
}

XttsTts::~XttsTts() {
    if (m_server) {
        m_server->terminate();
        if (!m_server->waitForFinished(3000)) m_server->kill();
    }
}

void XttsTts::start() {
    if (!m_available || m_server || m_pollTimer) return;

    // Riusa un server XTTS già in ascolto (es. riavvio rapido dell'app o server
    // lasciato da una chiusura brusca): evita conflitti di porta e il
    // ricaricamento del modello (~10-35s). Altrimenti ne avvio uno io.
    QNetworkReply* hr = m_net->get(QNetworkRequest(QUrl(m_host + QStringLiteral("/health"))));
    QTimer::singleShot(2500, hr, [hr]() { if (hr->isRunning()) hr->abort(); });
    connect(hr, &QNetworkReply::finished, this, [this, hr]() {
        hr->deleteLater();
        const bool alive = hr->error() == QNetworkReply::NoError &&
            hr->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200;
        if (!alive) launchServer();   // nessun server attivo: lo lancio
        beginReadyPolling();
    });
}

void XttsTts::launchServer() {
    if (m_server) return;
    m_server = new QProcess(this);
    m_server->setWorkingDirectory(QFileInfo(m_script).absolutePath());
    QStringList args{ m_script, QStringLiteral("--port"), QString::number(m_port) };
    if (!m_speakerWav.isEmpty() && QFileInfo::exists(m_speakerWav))
        args << QStringLiteral("--speaker-wav") << m_speakerWav;
    else if (!m_speaker.isEmpty())
        args << QStringLiteral("--speaker") << m_speaker;
    m_server->start(m_python, args);
}

void XttsTts::beginReadyPolling() {
    if (m_pollTimer) return;
    m_pollTries = 0;
    m_pollTimer = new QTimer(this);
    m_pollTimer->setInterval(kPollIntervalMs);
    connect(m_pollTimer, &QTimer::timeout, this, &XttsTts::pollReady);
    m_pollTimer->start();
    pollReady();   // primo controllo immediato (utile se riusiamo un server pronto)
}

void XttsTts::pollReady() {
    if (m_ready) { m_pollTimer->stop(); return; }
    if (++m_pollTries > kPollMaxTries) { m_pollTimer->stop(); return; }  // rinuncia: resta il fallback
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

void XttsTts::stopServer() {
    // Chiede lo spegnimento via HTTP (vale anche se il server è stato riusato),
    // poi termina il processo se l'abbiamo avviato noi. Resetta lo stato così
    // start() può rilanciarlo in seguito.
    if (m_net) {
        QNetworkReply* r = m_net->get(QNetworkRequest(QUrl(m_host + QStringLiteral("/shutdown"))));
        QTimer::singleShot(1500, r, [r]() { if (r->isRunning()) r->abort(); });
        connect(r, &QNetworkReply::finished, r, &QObject::deleteLater);
    }
    if (m_pollTimer) { m_pollTimer->stop(); m_pollTimer->deleteLater(); m_pollTimer = nullptr; }
    if (m_server) {
        m_server->terminate();
        if (!m_server->waitForFinished(2000)) m_server->kill();
        m_server->deleteLater();
        m_server = nullptr;
    }
    m_ready = false;
}

void XttsTts::say(const QString& text) {
    if (!m_ready || text.trimmed().isEmpty()) { emit finished(); return; }
    m_stopping = false;
    m_busy = true;

    const QByteArray body = QJsonDocument(
        QJsonObject{{"text", text}}).toJson(QJsonDocument::Compact);
    QNetworkRequest req{ QUrl(m_host + QStringLiteral("/tts")) };
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_ttsReply = m_net->post(req, body);

    QTimer::singleShot(kTtsTimeoutMs, m_ttsReply, [this]() {
        if (m_ttsReply && m_ttsReply->isRunning()) m_ttsReply->abort();
    });

    connect(m_ttsReply, &QNetworkReply::finished, this, [this]() {
        QNetworkReply* r = m_ttsReply;
        m_ttsReply = nullptr;
        if (!r) return;
        r->deleteLater();
        if (m_stopping) return;
        if (r->error() != QNetworkReply::NoError) {
            m_busy = false; emit finished();   // non bloccare la coda
            return;
        }
        const QByteArray wav = r->readAll();
        const QString tmp = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
        // Estensione in base al contenuto: WAV (Kokoro/XTTS) vs MP3 (edge-tts),
        // così QMediaPlayer riconosce il formato dal file.
        const char* ext = wav.startsWith("RIFF") ? "wav" : "mp3";
        m_curWav = QStringLiteral("%1/decodius_xtts_%2.%3").arg(tmp).arg(++m_counter).arg(QLatin1String(ext));
        QFile f(m_curWav);
        if (!f.open(QIODevice::WriteOnly) || f.write(wav) != wav.size()) {
            f.close(); m_busy = false; emit finished(); return;
        }
        f.close();
        startPlayback(m_curWav);
    });
}

void XttsTts::startPlayback(const QString& wav) {
    m_player->setSource(QUrl::fromLocalFile(wav));
    m_player->play();
}

void XttsTts::onPlaybackFinished() {
    m_player->stop();
    m_player->setSource(QUrl());
    if (!m_curWav.isEmpty()) { QFile::remove(m_curWav); m_curWav.clear(); }
    m_busy = false;
    if (!m_stopping) emit finished();
}

void XttsTts::stop() {
    m_stopping = true;
    // abort() emette finished() in modo SINCRONO: la lambda rientra e azzera
    // m_ttsReply. Lavoro su una copia locale, azzero PRIMA il membro e scollego la
    // reply, così la finished non rientra e non si dereferenzia un puntatore nullo.
    QNetworkReply* r = m_ttsReply;
    m_ttsReply = nullptr;
    if (r) { r->disconnect(this); r->abort(); r->deleteLater(); }
    if (m_player) { m_player->stop(); m_player->setSource(QUrl()); }
    if (!m_curWav.isEmpty()) { QFile::remove(m_curWav); m_curWav.clear(); }
    m_busy = false;
    // NB: non spegne il server (resta pronto per la prossima richiesta).
}
