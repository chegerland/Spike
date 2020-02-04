#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>

#include "ProgressBar.hpp"
#include "Spike.h"

// main
int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);
  std::string parameters = opts.get_parameter_file();

  // define neuron
  LIF lif(parameters);
  ExpAdaptation adapt(parameters);
  Timeframe time(parameters);

  std::vector<double> times;
  lif.spike_times(times, time);

  std::vector<double> intervals;

  for (int i = 0; i < times.size() - 1; i++) {
    intervals.push_back(times[i + 1] - times[i]);
    // std::cout << intervals[i] << std::endl;
  };

  double sum = std::accumulate(intervals.begin(), intervals.end(), 0.0);
  double mean = sum / intervals.size();

  std::vector<double> diff(intervals.size());
  std::transform(intervals.begin(), intervals.end(), diff.begin(),
                 std::bind2nd(std::minus<double>(), mean));
  double sq_sum =
      std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / intervals.size());

  double r0 = times.size() / time.get_t_end();
  double cv = stdev / mean;
  std::cout << "Mean: " << mean << std::endl;
  std::cout << "CV: " << cv << std::endl;
  std::cout << "Rate: " << r0 << std::endl;

  return 0;
};
