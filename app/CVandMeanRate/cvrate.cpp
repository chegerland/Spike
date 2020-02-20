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

  // define mu scale
  double mu = 0.5;
  double mu_end = 5.;
  double dmu = 0.05;
  int muSteps = (int)((mu_end - mu) / dmu);

  // define output file
  std::ofstream file;
  file.open(opts.get_output_file());

  std::vector<double> times;     // spike times
  std::vector<double> intervals; // interspike intervals
  std::vector<double> diff;
  double sum, mean, sq_sum, stdev, r0, cv;

  ProgressBar progbar(muSteps, 70);

  // loop over mu values
  for (int i = 0; i < muSteps; i++) {

    // clear
    times.clear();
    intervals.clear();

    // get spike times
    mu += dmu;
    lif.set_mu(mu);
    lif.spike_times(times, time, adapt);

    // calculate isi
    int end = times.size() - 1;
    for (int i = 0; i < end; i++) {
      intervals.push_back(times[i + 1] - times[i]);
    };

    // calculate statistics
    sum = mean = sq_sum = stdev = 0;
    sum = std::accumulate(intervals.begin(), intervals.end(), 0.0);
    mean = sum / intervals.size();
    diff.clear();
    diff.resize(intervals.size());
    std::transform(intervals.begin(), intervals.end(), diff.begin(),
                   std::bind2nd(std::minus<double>(), mean));
    sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    stdev = std::sqrt(sq_sum / intervals.size());

    // get firing rate and cv, write it to file
    r0 = times.size() / time.get_t_end();
    cv = stdev / mean;

    file << mu << "," << r0 << "," << cv << "\n";

    ++progbar;
    progbar.display();
  };

  progbar.done();

  return 0;
};
