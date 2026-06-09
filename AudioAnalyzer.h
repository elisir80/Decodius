// AudioAnalyzer.h — cattura il microfono (QtMultimedia) e produce, in tempo reale,
// il livello RMS e le bande spettrali che alimentano il visualizzatore Jarvis.
#pragma once
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QVariantList>
#include <QAudioSource>
#include <QAudioFormat>
#include <QIODevice>
#include <QByteArray>
#include <vector>

class AudioAnalyzer : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QVariantList levels READ levels NOTIFY updated)
    Q_PROPERTY(qreal rms READ rms NOTIFY updated)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)

public:
    explicit AudioAnalyzer(QObject* parent = nullptr);
    ~AudioAnalyzer() override;

    QVariantList levels() const { return m_levels; }
    qreal rms() const { return m_rms; }
    bool active() const { return m_active; }

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void updated();
    void activeChanged();

private slots:
    void onReadyRead();

private:
    void process();

    QAudioSource* m_source = nullptr;
    QIODevice*    m_io = nullptr;
    QByteArray    m_buffer;
    std::vector<float> m_samples;

    QAudioFormat m_format;                 // formato realmente concesso dal device
    int    m_sampleRate = 16000;
    size_t m_fftSize    = 1024;
    int    m_numBands   = 56;

    QVariantList m_levels;
    qreal m_rms = 0.0;
    bool  m_active = false;
};
