#include "statistics.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fftw3.h>
#include <numeric>

std::vector<double> get_spike_times(const SpikeTrain &spike_train,
                                    const TimeFrame &time) {
  assert(spike_train.get_length() == time.get_steps());

  std::vector<double> spike_times;

  for (size_t i = 0; i < spike_train.get_length(); i++) {
    if (spike_train.get_spike(i)) {
      spike_times.push_back(time.get_time(i));
    }
  }

  return spike_times;
}

// calculate the cv
double calculate_cv(const std::vector<double> &spike_times) {
  // calculate interspike intervals
  std::vector<double> intervals;
  intervals.resize(spike_times.size());

  for (size_t i = 0; i < spike_times.size() - 1; i++) {
    intervals.push_back(spike_times[i + 1] - spike_times[i]);
  }

  // sum and mean of the interspike intervals
  double sum = std::accumulate(intervals.begin(), intervals.end(), 0.0);
  double mean = sum / intervals.size();

  // calculate standard_deviation
  std::vector<double> diff(intervals.size());
  std::transform(intervals.begin(), intervals.end(), diff.begin(),
                 std::bind2nd(std::minus<double>(), mean));
  double sq_sum =
      std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / intervals.size());

  double cv = stdev / mean;

  return cv;
}

double mean(const std::vector<double> &values, const size_t length) {
  double mean = 0.0;
  for (size_t i = 0; i < length; i++) {
    mean += values[i];
  }
  return (double)mean / length;
}

double standard_deviation(const std::vector<double> &array,
                          const size_t length) {
  double mean_val = mean(array, length);
  double std = 0.0;

  for (size_t i = 0; i < length; i++) {
    std += (array[i] - mean_val) * (array[i] - mean_val);
  }

  return sqrt((double)std / length);
}

// calculate cross spectrum
void cross_spectrum(std::vector<double> &input_signal,
                    std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::complex<double> *spectrum) {

  // time step and array length
  double dt = time_frame.get_dt();
  size_t length = time_frame.get_steps();

  // vector for input signal fourier (isf)
  std::vector<std::complex<double>> isf;
  isf.resize(length / 2 + 1);

  // vector for output signal fourier (osf)
  std::vector<std::complex<double>> osf;
  osf.resize(length / 2 + 1);

  // fourier transform input signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(length, input_signal.data(),
                           reinterpret_cast<fftw_complex *>(isf.data()),
                           FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // fourier transform output signal
  fftw_plan p2;
#pragma omp critical
  p2 = fftw_plan_dft_r2c_1d(length, output_signal.data(),
                            reinterpret_cast<fftw_complex *>(osf.data()),
                            FFTW_ESTIMATE);
  fftw_execute(p2);
#pragma omp critical
  fftw_destroy_plan(p2);

  // fill cross spectrum, S_xy = x(omega) * y^*(omega)
  // normalize appropriately
  double scale = dt * dt / (time_frame.get_t_end() - time_frame.get_t_0());
  for (size_t i = 0; i < length / 2 + 1; i++) {
    spectrum[i] = scale * (isf[i] * std::conj(osf[i]));
  }
}

// calculate power spectrum
void power_spectrum(std::vector<double> &signal, const TimeFrame &time_frame,
                    std::vector<double> &spectrum) {

  // time step and array length
  double dt = time_frame.get_dt();
  size_t length = time_frame.get_steps();

  // vector for fourier transform of signal
  std::vector<std::complex<double>> signal_fourier;
  signal_fourier.resize(length / 2 + 1);

  // fourier transform signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(
      length, signal.data(),
      reinterpret_cast<fftw_complex *>(signal_fourier.data()), FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // calculate power spectrum and normalize appropriately!
  double scale = dt * dt / (time_frame.get_t_end() - time_frame.get_t_0());
  for (size_t i = 0; i < length / 2 + 1; i++) {
    spectrum[i] = scale * pow(std::abs(signal_fourier[i]), 2);
  }
}

// calculate susceptibility
void susceptibility(std::vector<double> &input_signal,
                    std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  size_t length = time_frame.get_steps();

  // vector for input signal fourier (isf)
  std::vector<std::complex<double>> isf;
  isf.resize(length / 2 + 1);

  // vector for output signal fourier (osf)
  std::vector<std::complex<double>> osf;
  osf.resize(length / 2 + 1);

  // fourier transform input signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(length, input_signal.data(),
                           reinterpret_cast<fftw_complex *>(isf.data()),
                           FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // fourier transform output signal
  fftw_plan p2;
#pragma omp critical
  p2 = fftw_plan_dft_r2c_1d(length, output_signal.data(),
                            reinterpret_cast<fftw_complex *>(osf.data()),
                            FFTW_ESTIMATE);
  fftw_execute(p2);
#pragma omp critical
  fftw_destroy_plan(p2);

  // fill susceptibility and normalize appropriately
  double dt = time_frame.get_dt();
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / pow(std::abs( dt * isf[i]), 2);
    suscept[i] = scale * (dt * osf[i] * dt * std::conj(isf[i]));
  }
}

void susceptibility(WhiteNoiseSignal &signal,
                    std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  size_t length = time_frame.get_steps();

  // vector for input signal fourier (isf)
  std::vector<std::complex<double>> isf;
  isf.resize(length / 2 + 1);

  // vector for output signal fourier (osf)
  std::vector<std::complex<double>> osf;
  osf.resize(length / 2 + 1);

  // fourier transform input signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(length, signal.get_values().data(),
                           reinterpret_cast<fftw_complex *>(isf.data()),
                           FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // fourier transform output signal
  fftw_plan p2;
#pragma omp critical
  p2 = fftw_plan_dft_r2c_1d(length, output_signal.data(),
                            reinterpret_cast<fftw_complex *>(osf.data()),
                            FFTW_ESTIMATE);
  fftw_execute(p2);
#pragma omp critical
  fftw_destroy_plan(p2);

  // fill susceptibility and normalize appropriately
  double dt = time_frame.get_dt();
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1./(pow(std::abs( dt * isf[i]),2));
    //double scale = 1. / signal.get_alpha();
    suscept[i] = scale * (dt * osf[i] * dt * std::conj(isf[i]));
  }
}

void susceptibility_nonlinear_diag(std::vector<double> &input_signal,
                                   std::vector<double> &output_signal,
                                   const TimeFrame &time_frame,
                                   std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  size_t length = time_frame.get_steps();

  // vector for input signal fourier (isf)
  std::vector<std::complex<double>> isf;
  isf.resize(length / 2 + 1);

  // vector for output signal fourier (osf)
  std::vector<std::complex<double>> osf;
  osf.resize(length / 2 + 1);

  // fourier transform input signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(length, input_signal.data(),
                           reinterpret_cast<fftw_complex *>(isf.data()),
                           FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // fourier transform output signal
  fftw_plan p2;
#pragma omp critical
  p2 = fftw_plan_dft_r2c_1d(length, output_signal.data(),
                            reinterpret_cast<fftw_complex *>(osf.data()),
                            FFTW_ESTIMATE);
  fftw_execute(p2);
#pragma omp critical
  fftw_destroy_plan(p2);

  // since the maximum frequency is at length/2 we choose to fill a square
  // matrix where each frequency only goes up to length/4.
  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 4; i++) {
    double scale = 1. / (2. * time_frame.get_dt() * pow(std::abs(isf[i]), 4));
    suscept[i] = scale * (osf[2 * i] * std::conj(isf[i]) * std::conj(isf[i]));
  }
}

void susceptibility_nonlinear_diag(WhiteNoiseSignal &signal,
                                   std::vector<double> &output_signal,
                                   const TimeFrame &time_frame,
                                   std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  size_t length = time_frame.get_steps();

  // vector for input signal fourier (isf)
  std::vector<std::complex<double>> isf;
  isf.resize(length / 2 + 1);

  // vector for output signal fourier (osf)
  std::vector<std::complex<double>> osf;
  osf.resize(length / 2 + 1);

  // fourier transform input signal
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(length, signal.get_values().data(),
                           reinterpret_cast<fftw_complex *>(isf.data()),
                           FFTW_ESTIMATE);
  fftw_execute(p);
#pragma omp critical
  fftw_destroy_plan(p);

  // fourier transform output signal
  fftw_plan p2;
#pragma omp critical
  p2 = fftw_plan_dft_r2c_1d(length, output_signal.data(),
                            reinterpret_cast<fftw_complex *>(osf.data()),
                            FFTW_ESTIMATE);
  fftw_execute(p2);
#pragma omp critical
  fftw_destroy_plan(p2);

  // since the maximum frequency is at length/2 we choose to fill a square
  // matrix where each frequency only goes up to length/4.
  // fill susceptibility and normalize appropriately
  double dt = time_frame.get_dt();
  //double variance = signal.get_variance() / (time_frame.get_t_end() - time_frame.get_t_0());
  for (size_t i = 0; i < length / 4; i++) {
    double scale = 1. / (2. * pow(std::abs( dt * isf[i]), 4));
    //double scale = 1. / (2. * signal.get_alpha() * signal.get_alpha());
    //double scale = 1./ ( 2. * pow(variance, 2));
    suscept[i] = scale * (dt * osf[2 * i] * dt * std::conj(isf[i]) * dt *
                          std::conj(isf[i]));
  }
}

void add_spike_train_to_kernel(const SpikeTrain &spike_train,
                               const Signal &signal,
                               const TimeFrame &time_frame, double norm,
                               double *kernel) {

  for (size_t i = 0; i < time_frame.get_steps(); i++) {
    if (spike_train.get_spike(i)) {
      for (size_t j = 0; j < i; j++) {
        kernel[j] += norm * signal.get_value(i - j);
      }
    }
  }
}
