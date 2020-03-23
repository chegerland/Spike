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

  // calculate stdev
  std::vector<double> diff(intervals.size());
  std::transform(intervals.begin(), intervals.end(), diff.begin(),
                 std::bind2nd(std::minus<double>(), mean));
  double sq_sum =
      std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / intervals.size());

  double cv = stdev / mean;

  return cv;
}

void fourier_transform_firing_rate(
    const std::vector<double> &firing_rate, const TimeFrame &time,
    std::vector<double> &frequencies,
    std::vector<std::complex<double>> &firing_rate_fourier) {

  // check size of vectors
  unsigned int steps = time.get_steps();
  assert(firing_rate_fourier.size() == steps / 2 + 1);
  assert(frequencies.size() == steps / 2 + 1);

  // create right types for fftw
  double *in;
  in = (double *)malloc(sizeof(double) * steps);

  for (unsigned int i = 0; i < steps; i++) {
    in[i] = firing_rate[i];
  }

  fftw_complex *out;
  out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (steps / 2 + 1));

  // calculate susceptibility
  fftw_plan p;
  p = fftw_plan_dft_r2c_1d(steps, in, out, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  // define imaginary unit and scale for output
  std::complex<double> I(0.0, 1.0);
  const double scale = time.get_dt();

  // write output in firing_rate_fourier
  for (unsigned int i = 0; i < steps / 2 + 1; i++) {
    firing_rate_fourier[i] = scale * (out[i][0] + I * out[i][1]);
    frequencies[i] = (double)i * 1. / (time.get_t_end() - time.get_t_0());
  }

  fftw_free(out);
  delete[] in;
}
