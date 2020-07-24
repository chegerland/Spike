#ifndef FFT_H
#define FFT_H

#include "../TimeFrame/TimeFrame.h"
#include <complex>
#include <vector>

/**
 * @brief Wraps the fftw routine fftw_plan_dft_r2c_1d. Multiplies each
 * entry of signal_fourier by dt for correct normalization.
 * @param dt Time step
 * @param signal Vector containing signal values
 * @param signal_fourier Vector containing Fourier transform of signal
 */
void fft_r2c(double dt, const std::vector<double> &signal,
             std::vector<std::complex<double>> &signal_fourier);

/**
 * @brief Wraps the fftw routine fftw_plan_dft_c2r_1d. Divides each
 * entry of signal_fourier by dt*signal.size() for correct normalization
 * @param dt Time step
 * @param signal_fourier Vector containing Fourier transform of signal
 * @param signal Vector containing signal values
 */
void fft_c2r(double dt, const std::vector<std::complex<double>> &signal_fourier,
             std::vector<double> &signal);

#endif // FFT_H
