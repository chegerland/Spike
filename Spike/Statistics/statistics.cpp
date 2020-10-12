#include <algorithm>
#include <cmath>
#include <fftw3.h>
#include <numeric>

#include "Spike/FFT/fft.h"
#include "Spike/Statistics/statistics.h"

namespace Spike {

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

double mean(const std::vector<double> &values) {
  double mean = 0.0;
  for (const auto &elem : values) {
    mean += elem;
  }
  return (double)mean / values.size();
}

double standard_deviation(const std::vector<double> &array) {
  double mean_val = mean(array);
  double std = 0.0;

  for (const auto &elem : array) {
    std += (elem - mean_val) * (elem - mean_val);
  }

  return sqrt((double)std / array.size());
}

// calculate cross spectrum
void cross_spectrum(const std::vector<double> &input_signal,
                    const std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::complex<double> *spectrum) {

  // time step and array length
  const double dt = time_frame.get_dt();
  const size_t length = time_frame.get_size();

  assert(input_signal.size() == length);
  assert(output_signal.size() == length);

  // vector for input signal fourier (isf) and output signal fourier (osf)
  std::vector<std::complex<double>> isf(length / 2 + 1);
  std::vector<std::complex<double>> osf(length / 2 + 1);

  fft_r2c(dt, input_signal, isf);
  fft_r2c(dt, output_signal, osf);

  // fill cross spectrum, S_xy = x(omega) * y^*(omega)
  // normalize appropriately
  const double scale = 1. / (time_frame.get_t_end() - time_frame.get_t_0());
  for (size_t i = 0; i < length / 2 + 1; i++) {
    spectrum[i] = scale * (isf[i] * std::conj(osf[i]));
  }
}

// calculate power spectrum
void power_spectrum(const std::vector<double> &signal,
                    const TimeFrame &time_frame,
                    std::vector<double> &spectrum) {

  // time step and array length
  const double dt = time_frame.get_dt();
  const size_t length = time_frame.get_size();

  // vector for fourier transform of signal
  std::vector<std::complex<double>> signal_fourier(length / 2 + 1);

  fft_r2c(dt, signal, signal_fourier);

  // calculate power spectrum and normalize appropriately!
  const double scale = 1. / (time_frame.get_t_end() - time_frame.get_t_0());
  for (size_t i = 0; i < length / 2 + 1; i++) {
    spectrum[i] = scale * pow(std::abs(signal_fourier[i]), 2);
  }
}

// calculate susceptibility
void susceptibility(const std::vector<double> &input_signal,
                    const std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  const double dt = time_frame.get_dt();
  const size_t length = time_frame.get_size();

  // vector for input signal fourier (isf) and output signal fourier (osf)
  std::vector<std::complex<double>> isf(length / 2 + 1);
  std::vector<std::complex<double>> osf(length / 2 + 1);

  fft_r2c(dt, input_signal, isf);
  fft_r2c(dt, output_signal, osf);

  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / pow(std::abs(dt * isf[i]), 2);
    suscept[i] = scale * (osf[i] * std::conj(isf[i]));
  }
}

void susceptibility(const WhiteNoiseSignal &signal,
                    const std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  const size_t length = time_frame.get_size();

  // vector for input signal fourier (isf)
  std::vector<std::complex<double>> isf = signal.get_frequencies();

  // vector for output signal fourier (osf)
  std::vector<std::complex<double>> osf(length / 2 + 1);

  fft_r2c(time_frame.get_dt(), output_signal, osf);

  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 2 + 1; i++) {
    double scale = 1. / (pow(std::abs(isf[i]), 2));
    suscept[i] = scale * (osf[i] * std::conj(isf[i]));
  }
}

void susceptibility_nonlinear_diag(const std::vector<double> &input_signal,
                                   const std::vector<double> &output_signal,
                                   const TimeFrame &time_frame,
                                   std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  size_t length = time_frame.get_size();

  // vector for input signal fourier (isf) and output signal fourier (osf)
  std::vector<std::complex<double>> isf(length / 2 + 1);
  std::vector<std::complex<double>> osf(length / 2 + 1);

  fft_r2c(time_frame.get_dt(), input_signal, isf);
  fft_r2c(time_frame.get_dt(), output_signal, osf);

  // since the maximum frequency is at length/2 we choose to fill a square
  // matrix where each frequency only goes up to length/4.
  // fill susceptibility and normalize appropriately
  for (size_t i = 0; i < length / 4; i++) {
    double scale = 1. / (2. * time_frame.get_dt() * pow(std::abs(isf[i]), 4));
    suscept[i] = scale * (osf[2 * i] * std::conj(isf[i]) * std::conj(isf[i]));
  }
}

void susceptibility_nonlinear_diag(const WhiteNoiseSignal &signal,
                                   const std::vector<double> &output_signal,
                                   const TimeFrame &time_frame,
                                   std::vector<std::complex<double>> &suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  const size_t length = time_frame.get_size();
  const double dt = time_frame.get_dt();

  // vector for input signal fourier (isf)
  const std::vector<std::complex<double>>& isf = signal.get_frequencies();

  // vector for output signal fourier (osf)
  std::vector<std::complex<double>> osf(length / 2 + 1);

  fft_r2c(dt, output_signal, osf);

  // since the maximum frequency is at length/2 we choose to fill a square
  // matrix where each frequency only goes up to length/4.
  // fill susceptibility and normalize appropriately
  // double variance = signal.get_variance() / (time_frame.get_t_end() -
  // time_frame.get_t_0());
  for (size_t i = 0; i < length / 4; i++) {
    double scale = 1. / (2. * pow(std::abs(isf[i]), 4));
    suscept[i] = scale * (osf[2 * i] * std::conj(isf[i]) * std::conj(isf[i]));
  }
}

void susceptibility_lin_nonlin(
    const WhiteNoiseSignal &signal, const std::vector<double> &output_signal,
    const TimeFrame &time_frame, std::vector<std::complex<double>> &suscept_lin,
    std::vector<std::complex<double>> &suscept_nonlin, const size_t norm) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we
  // perform real DFT
  const size_t length = time_frame.get_size();
  const double dt = time_frame.get_dt();
  const double T = time_frame.get_t_end() - time_frame.get_t_0();

  // vector for input signal fourier (isf) and output signal fourier (osf)
  const std::vector<std::complex<double>>& isf = signal.get_frequencies();
  std::vector<std::complex<double>> osf(length / 2 + 1);

  fft_r2c(dt, output_signal, osf);

  double scale_lin = 0., scale_nonlin = 0.;
  for (size_t i = 0; i < length / 4 + 1; i++) {
    scale_lin = 1. / (((double)norm) * pow(std::abs(isf[i]), 2));
    scale_nonlin = T / (((double)norm) * 2. * pow(std::abs(isf[i]), 4));
    suscept_lin[i] += scale_lin * (osf[i] * std::conj(isf[i]));
    suscept_nonlin[i] +=
        scale_nonlin * (osf[i + i] * std::conj(isf[i]) * std::conj(isf[i]));
  }

  for (size_t i = length / 4 + 1; i < length / 2 + 1; i++) {
    scale_lin = 1. / (((double)norm) * pow(std::abs(isf[i]), 2));
    suscept_lin[i] += scale_lin * (osf[i] * std::conj(isf[i]));
  }
}

void add_spike_train_to_kernel(const SpikeTrain &spike_train,
                               const Signal &signal,
                               const TimeFrame &time_frame, double norm,
                               double *kernel) {

  for (size_t i = 0; i < time_frame.get_size(); i++) {
    if (spike_train.get_spike(i)) {
      for (size_t j = 0; j < i; j++) {
        kernel[j] += norm * signal.get_value(i - j);
      }
    }
  }
}

} // namespace Spike