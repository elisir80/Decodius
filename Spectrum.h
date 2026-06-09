// Spectrum.h — logica pura di analisi spettrale (niente Qt).
// Trasforma un blocco di campioni audio in: livello RMS + N bande log-spaziate
// (i "bastoncini" del visualizzatore Jarvis).
#pragma once
#include "Fft.h"
#include <vector>
#include <algorithm>
#include <cmath>

namespace dsp {

struct AnalysisResult {
    float rms = 0.0f;            // ampiezza complessiva 0..~1 (per il glow / scala)
    std::vector<float> bands;    // magnitudini normalizzate 0..1 per banda
};

// samples: mono, range tipico [-1,1]. fftSize potenza di 2 (es. 1024).
// numBands: quante barre vuoi nel visualizzatore (es. 48).
// sampleRate: per mappare le bande in frequenza (log).
inline AnalysisResult analyze(const std::vector<float>& samples,
                              size_t fftSize, int numBands, int sampleRate) {
    AnalysisResult out;
    out.bands.assign(numBands, 0.0f);
    if (samples.size() < fftSize) return out;

    // RMS
    double acc = 0.0;
    for (size_t i = 0; i < fftSize; ++i) acc += double(samples[i]) * samples[i];
    out.rms = float(std::sqrt(acc / fftSize));

    // Finestra di Hann + FFT
    std::vector<std::complex<float>> buf(fftSize);
    for (size_t i = 0; i < fftSize; ++i)
        buf[i] = std::complex<float>(samples[i] * hann(i, fftSize), 0.0f);
    fft(buf);

    // Magnitudine (solo metà utile dello spettro)
    const size_t half = fftSize / 2;
    std::vector<float> mag(half);
    for (size_t i = 0; i < half; ++i)
        mag[i] = std::abs(buf[i]) / float(fftSize);

    // Bande log-spaziate da ~80 Hz a Nyquist: percezione più "musicale".
    const float fMin = 80.0f;
    const float fMax = float(sampleRate) / 2.0f;
    const float binHz = float(sampleRate) / float(fftSize);

    for (int b = 0; b < numBands; ++b) {
        float lo = fMin * std::pow(fMax / fMin, float(b) / numBands);
        float hi = fMin * std::pow(fMax / fMin, float(b + 1) / numBands);
        size_t i0 = std::max<size_t>(1, size_t(lo / binHz));
        size_t i1 = std::min<size_t>(half - 1, size_t(hi / binHz));
        if (i1 < i0) i1 = i0;

        float peak = 0.0f;
        for (size_t i = i0; i <= i1; ++i) peak = std::max(peak, mag[i]);

        // Scala log (dB-like) e normalizzazione morbida per il display.
        float db = 20.0f * std::log10(peak + 1e-6f);     // ~ -120..0
        float norm = (db + 70.0f) / 70.0f;               // mappa -70..0 dB -> 0..1
        out.bands[b] = std::clamp(norm, 0.0f, 1.0f);
    }
    return out;
}

} // namespace dsp
