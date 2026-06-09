// PiperTts.cpp
#include "PiperTts.h"
#include <QProcess>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QStandardPaths>

PiperTts::PiperTts(const QString& exePath, const QString& modelPath, QObject* parent)
    : QObject(parent), m_exe(exePath), m_model(modelPath) {
    m_available = QFileInfo::exists(m_exe) && QFileInfo::exists(m_model);
    if (!m_available) return;

    m_audio = new QAudioOutput(this);
    m_audio->setVolume(1.0);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_audio);

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this,
            [this](QMediaPlayer::MediaStatus s) {
        if (s == QMediaPlayer::EndOfMedia) onPlaybackFinished();
    });
}

void PiperTts::say(const QString& text) {
    if (!m_available || text.trimmed().isEmpty()) { emit finished(); return; }

    m_stopping = false;
    m_busy = true;

    // File WAV temporaneo univoco (evita lock con la riproduzione precedente).
    const QString tmp = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    m_curWav = QStringLiteral("%1/decodius_tts_%2.wav").arg(tmp).arg(++m_counter);

    m_proc = new QProcess(this);
    m_proc->setWorkingDirectory(QFileInfo(m_exe).absolutePath());  // per trovare espeak-ng-data
    connect(m_proc, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), this,
            [this](int, QProcess::ExitStatus) {
        if (m_proc) { m_proc->deleteLater(); m_proc = nullptr; }
        if (m_stopping) return;
        if (QFileInfo::exists(m_curWav)) {
            startPlayback(m_curWav);
        } else {
            m_busy = false;
            emit finished();   // sintesi fallita: non bloccare la coda
        }
    });

    // Parametri di resa: ritmo leggermente più calmo e maggiore variabilità
    // prosodica per un tono più naturale (meno "robotico").
    m_proc->start(m_exe, {QStringLiteral("-m"), m_model,
                          QStringLiteral("-f"), m_curWav,
                          QStringLiteral("--length_scale"), QStringLiteral("1.05"),
                          QStringLiteral("--noise_scale"),  QStringLiteral("0.667"),
                          QStringLiteral("--noise_w"),      QStringLiteral("0.9"),
                          QStringLiteral("--sentence_silence"), QStringLiteral("0.2")});
    m_proc->write(text.toUtf8());
    m_proc->closeWriteChannel();
}

void PiperTts::startPlayback(const QString& wav) {
    m_player->setSource(QUrl::fromLocalFile(wav));
    m_player->play();
}

void PiperTts::onPlaybackFinished() {
    m_player->stop();
    m_player->setSource(QUrl());     // rilascia il file
    if (!m_curWav.isEmpty()) { QFile::remove(m_curWav); m_curWav.clear(); }
    m_busy = false;
    if (!m_stopping) emit finished();
}

void PiperTts::stop() {
    m_stopping = true;
    if (m_proc) {
        m_proc->kill();
        m_proc->deleteLater();
        m_proc = nullptr;
    }
    if (m_player) {
        m_player->stop();
        m_player->setSource(QUrl());
    }
    if (!m_curWav.isEmpty()) { QFile::remove(m_curWav); m_curWav.clear(); }
    m_busy = false;
}
