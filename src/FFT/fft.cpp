/*
 * @file fft.h
 * @author C. H. Egerland
 */
#include "fft.h"
#include <cassert>
#include <fftw3.h>

void fft_r2c(size_t length, double dt, const std::vector<double> &signal,
             std::vector<std::complex<double>> &signal_fourier) {

  // check for right size of the arrays
  assert(signal.size() == length);
  assert(signal_fourier.size() == length / 2 + 1);

  // fourier transform the signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(
      length, const_cast<double *>(signal.data()),
      reinterpret_cast<fftw_complex *>(signal_fourier.data()), FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // normalize the signal correctly
  for (auto & i : signal_fourier) {
    i *= dt;
  }
}

void fft_c2r(size_t length, double dt,
             const std::vector<std::complex<double>> &signal_fourier,
             std::vector<double> &signal) {

  // check for right size of the arrays
  assert(signal.size() == length);
  assert(signal_fourier.size() == length / 2 + 1);

  // fourier transform the signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_c2r_1d(
      length,
      reinterpret_cast<fftw_complex *>(
          const_cast<std::complex<double> *>(signal_fourier.data())),
      signal.data(), FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // normalize the signal correctly
  for (double & i : signal) {
    i /= dt * length;
  }
}
