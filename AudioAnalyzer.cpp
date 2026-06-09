// AudioAnalyzer.cpp
#include "AudioAnalyzer.h"
#include "Spectrum.h"
#include <QMediaDevices>
#include <QtMath>
#include <cstring>

AudioAnalyzer::AudioAnalyzer(QObject* parent) : QObject(parent) {
    m_levels.reserve(m_numBands);
    for (int i = 0; i < m_numBands; ++i) m_levels.append(0.0);
}

AudioAnalyzer::~AudioAnalyzer() { stop(); }

void AudioAnalyzer::start() {
    if (m_active) return;

    QAudioFormat fmt;
    fmt.setSampleRate(m_sampleRate);
    fmt.setChannelCount(1);
    fmt.setSampleFormat(QAudioFormat::Float);

    const QAudioDevice dev = QMediaDevices::defaultAudioInput();
    if (dev.isNull()) {
        qWarning("Nessun dispositivo di input audio trovato.");
        return;
    }
    if (!dev.isFormatSupported(fmt)) {
        fmt = dev.preferredFormat();
        m_sampleRate = fmt.sampleRate();
    }

    m_format = fmt;                        // ricordo il formato effettivo per la decodifica
    m_source = new QAudioSource(dev, fmt, this);
    m_io = m_source->start();              // pull mode
    if (!m_io) {
        qWarning("Impossibile avviare la cattura audio.");
        delete m_source; m_source = nullptr;
        return;
    }
    connect(m_io, &QIODevice::readyRead, this, &AudioAnalyzer::onReadyRead);
    m_active = true;
    emit activeChanged();
}

void AudioAnalyzer::stop() {
    if (m_source) { m_source->stop(); m_source->deleteLater(); m_source = nullptr; }
    m_io = nullptr;
    m_buffer.clear();
    m_samples.clear();
    if (m_active) { m_active = false; emit activeChanged(); }
}

// Converte un singolo campione (puntatore al primo byte) nel range float [-1,1],
// secondo il sampleFormat realmente concesso dal device.
static inline float sampleToFloat(const char* p, QAudioFormat::SampleFormat sf) {
    switch (sf) {
    case QAudioFormat::Float: {
        float v; std::memcpy(&v, p, sizeof(float)); return v;
    }
    case QAudioFormat::Int16: {
        qint16 v; std::memcpy(&v, p, sizeof(qint16));
        return float(v) / 32768.0f;
    }
    case QAudioFormat::Int32: {
        qint32 v; std::memcpy(&v, p, sizeof(qint32));
        return float(double(v) / 2147483648.0);
    }
    case QAudioFormat::UInt8:
        return (float(quint8(*p)) - 128.0f) / 128.0f;
    default:
        return 0.0f;
    }
}

void AudioAnalyzer::onReadyRead() {
    if (!m_io) return;
    m_buffer.append(m_io->readAll());

    const int bytesPerFrame = m_format.bytesPerFrame();   // campione * canali
    const int channels      = qMax(1, m_format.channelCount());
    const int bytesPerSample = bytesPerFrame / channels;
    if (bytesPerFrame <= 0) return;

    // Accumulo finché non ho almeno fftSize frame.
    const int avail = m_buffer.size() / bytesPerFrame;    // frame disponibili
    if (avail < int(m_fftSize)) return;

    // Decodifico in mono float (media dei canali) secondo il formato effettivo.
    const QAudioFormat::SampleFormat sf = m_format.sampleFormat();
    const char* base = m_buffer.constData();
    m_samples.resize(avail);
    for (int f = 0; f < avail; ++f) {
        const char* frame = base + qsizetype(f) * bytesPerFrame;
        float acc = 0.0f;
        for (int c = 0; c < channels; ++c)
            acc += sampleToFloat(frame + c * bytesPerSample, sf);
        m_samples[f] = acc / float(channels);
    }

    process();

    // Consumo i frame elaborati (in byte).
    m_buffer.remove(0, qsizetype(avail) * bytesPerFrame);
}

void AudioAnalyzer::process() {
    auto r = dsp::analyze(m_samples, m_fftSize, m_numBands, m_sampleRate);
    for (int i = 0; i < m_numBands && i < int(r.bands.size()); ++i)
        m_levels[i] = qreal(r.bands[i]);
    m_rms = qreal(r.rms);
    emit updated();
}
