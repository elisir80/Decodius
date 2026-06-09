// Fft.h — FFT radix-2 (Cooley-Tukey), header-only, nessuna dipendenza.
// Usato dall'analizzatore audio per ricavare lo spettro dall'onda del microfono.
#pragma once
#include <vector>
#include <complex>
#include <cmath>

namespace dsp {

// FFT in-place su un vettore la cui dimensione DEVE essere potenza di 2.
inline void fft(std::vector<std::complex<float>>& a) {
    const size_t n = a.size();
    if (n <= 1) return;

    // Bit-reversal
    for (size_t i = 1, j = 0; i < n; ++i) {
        size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }

    // Butterfly
    for (size_t len = 2; len <= n; len <<= 1) {
        const float ang = -2.0f * float(M_PI) / float(len);
        const std::complex<float> wlen(std::cos(ang), std::sin(ang));
        for (size_t i = 0; i < n; i += len) {
            std::complex<float> w(1.0f, 0.0f);
            for (size_t k = 0; k < len / 2; ++k) {
                std::complex<float> u = a[i + k];
                std::complex<float> v = a[i + k + len / 2] * w;
                a[i + k] = u + v;
                a[i + k + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
}

// Finestra di Hann, riduce le perdite spettrali.
inline float hann(size_t i, size_t n) {
    return 0.5f * (1.0f - std::cos(2.0f * float(M_PI) * float(i) / float(n - 1)));
}

} // namespace dsp
