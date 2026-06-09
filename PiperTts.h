// PiperTts.h — sintesi vocale neurale offline tramite piper.exe.
// Sintetizza un blocco di testo in WAV (QProcess) e lo riproduce (QMediaPlayer),
// emettendo finished() a riproduzione conclusa così la coda TTS può avanzare.
#pragma once
#include <QObject>
#include <QString>

class QProcess;
class QMediaPlayer;
class QAudioOutput;

class PiperTts : public QObject {
    Q_OBJECT
public:
    PiperTts(const QString& exePath, const QString& modelPath, QObject* parent = nullptr);

    bool isAvailable() const { return m_available; }
    bool isBusy() const { return m_busy; }

    void say(const QString& text);   // sintetizza e riproduce un blocco
    void stop();                     // interrompe sintesi e riproduzione correnti

signals:
    void finished();                 // riproduzione del blocco terminata (idle)

private:
    void startPlayback(const QString& wav);
    void onPlaybackFinished();

    QString m_exe;
    QString m_model;
    bool    m_available = false;
    bool    m_busy = false;
    bool    m_stopping = false;
    int     m_counter = 0;
    QString m_curWav;

    QProcess*     m_proc = nullptr;
    QMediaPlayer* m_player = nullptr;
    QAudioOutput* m_audio = nullptr;
};
