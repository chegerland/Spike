#ifndef FFT_H
#define FFT_H

#include <complex>
#include <vector>

void fft_r2c(double dt, const std::vector<double> &signal,
                    std::vector<std::complex<double>> &signal_fourier);
void fft_c2r(double dt,
                    const std::vector<std::complex<double>> &signal_fourier,
                    std::vector<double> &signal);

#endif // FFT_H
