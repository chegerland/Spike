/*
 * @file fft.h
 * @author C. H. Egerland
 */
#ifndef FFT_H
#define FFT_H

#include <complex>
#include <vector>

/**
 * @brief Wrapper around the fftw_plan_dft_r2c_1d method.
 * The signal array has size length and the signal_fourier array has size
 * length/2 + 1.
 * @param length Array length of the signal
 * @param dt Time step
 * @param signal Array containing signal values
 * @param signal_fourier Array containing the fourier transform
 */
void fft_r2c(size_t length, double dt, const std::vector<double> &signal,
             std::vector<std::complex<double>> &signal_fourier);

/**
 * @brief Wrapper around the fftw_plan_dft_c2r_1d method.
 * The signal array has size length and the signal_fourier array has size
 * length/2 + 1.
 * @param length Array length of the signal
 * @param dt Time step
 * @param signal_fourier Array containing the fourier transform
 * @param signal Array containing signal values
 */
void fft_c2r(size_t length, double dt,
             const std::vector<std::complex<double>> &signal_fourier,
             std::vector<double> &signal);

#endif // FFT_H
