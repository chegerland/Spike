#include "statistics.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

// add single spike train to firing rate
void add_to_firing_rate(const std::vector<bool> &spike_train,
                        const Timeframe &time,
                        std::vector<double> &firing_rate) {
  // arrays should have same length
  assert(firing_rate.size() == spike_train.size());

  double dt = time.get_dt();

  // add 1/dt if neuron has spiked
  for (unsigned int i = 0; i < spike_train.size(); i++) {

    if (spike_train[i] == true) {
      firing_rate[i] += 1. / dt;
    };
  };
};

// add ensemble spike train to firing rate
void add_to_firing_rate(const std::vector<bool> &spike_train,
                        const Timeframe &time, const int N,
                        std::vector<double> &firing_rate) {
  // arrays should have same length
  assert(firing_rate.size() == spike_train.size());

  double dt = time.get_dt();

  // add 1/dt if neuron has spiked
  for (unsigned int i = 0; i < spike_train.size(); i++) {

    if (spike_train[i] == true) {
      firing_rate[i] += 1. / ((double)N * dt);
    };
  };
};

// calculate the spike times
std::vector<double> get_spike_times(const std::vector<bool> &spike_train,
                                    const Timeframe &time) {
  assert(spike_train.size() == time.get_steps());

  std::vector<double> spike_times;

  double t = time.get_t_0();
  double dt = time.get_dt();
  for (unsigned int i = 0; i < spike_train.size(); i++) {
    t += dt;
    if (spike_train[i] == true) {
      spike_times.push_back(t);
    };
  };

  return spike_times;
};

// calculate the cv
double calculate_cv(const std::vector<double> &spike_times) {
  // calculate interspike intervals
  std::vector<double> intervals;
  intervals.resize(spike_times.size());

  for (unsigned int i = 0; i < spike_times.size() - 1; i++) {
    intervals.push_back(spike_times[i + 1] - spike_times[i]);
  };

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
};

// count the spikes
int spike_count(const std::vector<bool> &spike_train) {
  int count = 0;

  for (unsigned int i = 0; i < spike_train.size(); i++) {
    if (spike_train[i] == true) {
      count++;
    };
  };

  return count;
};
