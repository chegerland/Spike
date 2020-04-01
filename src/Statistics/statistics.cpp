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

  for (unsigned int i = 0; i < spike_train.get_length(); i++) {
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

  for (unsigned int i = 0; i < spike_times.size() - 1; i++) {
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

double mean(const double *values, const int N) {
  double mean = 0.0;
  for (int i = 0; i < N; i++) {
    mean += values[i];
  }
  return (double) mean/N;
}

double standard_deviation(const double *array, const int length) {
  double mean_val = mean(array, length);
  double std = 0.0;

  for (int i = 0; i < length; i++) {
    std += (array[i] - mean_val) * (array[i] - mean_val);
  }

  return sqrt((double) std/length);
}

void shorten_array(const double *array_long, const TimeFrame &time_frame_long,
                   const TimeFrame &time_frame_short, double *array_short) {
  assert(time_frame_long.get_t_end() == time_frame_short.get_t_end());
  assert(time_frame_long.get_dt() == time_frame_short.get_dt());

  const int cut_index = time_frame_long.get_steps() - time_frame_short.get_steps();

  for(int i = 0; i < time_frame_short.get_steps(); i++) {
    array_short[i] = array_long[cut_index + i];
  }
}

// calculate cross spectrum
void cross_spectrum(double *input_signal, double *output_signal,
                    const TimeFrame& time_frame, fftw_complex *spectrum) {

  int length = (int)time_frame.get_steps();

  // time step
  double dt = time_frame.get_dt();

  // fourier transform first signal
  // length of the fourier transform is N/2 + 1 because we perform real DFT
  fftw_plan p;
  fftw_complex *input_signal_fourier;
  input_signal_fourier = new fftw_complex [length/2 + 1];

  p = fftw_plan_dft_r2c_1d(length, input_signal, input_signal_fourier,
                           FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  // fourier transform second signal
  fftw_plan p2;
  fftw_complex *output_signal_fourier;
  output_signal_fourier = new fftw_complex [length];
  p2 = fftw_plan_dft_r2c_1d(length, output_signal, output_signal_fourier,
                            FFTW_ESTIMATE);
  fftw_execute(p2);
  fftw_destroy_plan(p2);

  // fill cross spectrum, S_xy = x(omega) * y^*(omega)
  // normalize appropriately
  double scale = dt * dt / (time_frame.get_t_end() - time_frame.get_t_0());
  for (int i = 0; i < length/2 + 1; i++) {
    spectrum[i][0] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][0] +
                 input_signal_fourier[i][1] * output_signal_fourier[i][1]);
    spectrum[i][1] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][1] -
                 input_signal_fourier[i][1] * output_signal_fourier[i][0]);
  }

  // free memory
  delete [] input_signal_fourier;
  delete [] output_signal_fourier;
}

// calculate power spectrum
void power_spectrum(double *signal, const TimeFrame& time_frame,
                    double *spectrum) {
  // length of the signals is N/2 + 1 because we perform real DFT
  int length = (int)time_frame.get_steps();

  // time step
  double dt = time_frame.get_dt();

  // fourier transform first signal
  fftw_plan p;
  fftw_complex *signal_fourier;
  signal_fourier = new fftw_complex [length/2 + 1];
  p = fftw_plan_dft_r2c_1d(length, signal, signal_fourier, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  // calculate power spectrum and normalize appropriately!
  double scale = dt * dt / (time_frame.get_t_end() - time_frame.get_t_0());
  for (int i = 0; i < length/2 + 1; i++) {
    spectrum[i] = scale * (signal_fourier[i][0] * signal_fourier[i][0] +
                           signal_fourier[i][1] * signal_fourier[i][1]);
  }

  // free memory
  delete [] signal_fourier;
}

// calculate susceptibility
void susceptibility(double *input_signal, double *output_signal,
                    const TimeFrame& time_frame, fftw_complex *suscept) {

  // length of the signals is N, fourier transform will be N/2 + 1 because we perform real DFT
  int length = (int)time_frame.get_steps();

  // fourier transform first signal
  fftw_plan p;
  fftw_complex *input_signal_fourier;
  input_signal_fourier = new fftw_complex [length/2 + 1];
#pragma omp critical
  p = fftw_plan_dft_r2c_1d(length, input_signal, input_signal_fourier,
                           FFTW_ESTIMATE);

  fftw_execute(p);

#pragma omp critical
  fftw_destroy_plan(p);

  // fourier transform second signal
  fftw_plan p2;
  fftw_complex *output_signal_fourier;
  output_signal_fourier = new fftw_complex [length/2 + 1];
#pragma omp critical
  p2 = fftw_plan_dft_r2c_1d(length, output_signal, output_signal_fourier,
                            FFTW_ESTIMATE);

  fftw_execute(p2);

#pragma omp critical
  fftw_destroy_plan(p2);

  // fill susceptibility and normalize appropriately
  double scale;
  for (int i = 0; i < length/2 + 1; i++) {
    scale = 1. /
            (input_signal_fourier[i][0] * input_signal_fourier[i][0] +
             input_signal_fourier[i][1] * input_signal_fourier[i][1]);
    suscept[i][0] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][0] +
                 input_signal_fourier[i][1] * output_signal_fourier[i][1]);
    suscept[i][1] =
        scale * (input_signal_fourier[i][0] * output_signal_fourier[i][1] -
                 input_signal_fourier[i][1] * output_signal_fourier[i][0]);
  }

  // free memory
  delete [] input_signal_fourier;
  delete [] output_signal_fourier;
}

