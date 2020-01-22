#include <fstream>
#include <iostream>

#include "ProgressBar.hpp"
#include "Spike.h"

// main
int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);
  std::string parameters = opts.get_parameter_file();

  // define LIF neuron with adaptation and signal
  LIF neuron(parameters);
  Signal *signal = SignalFactory::create(parameters);
  ExpAdaptation adapt(parameters);

  // define simulation time frame
  Timeframe time(parameters);

  // array to put firing rate into
  std::vector<double> rate;
  rate.resize(time.get_steps());

  // get firing rate
  int N_sims = 100000;

  ProgressBar progbar(N_sims, 70);

#pragma omp parallel for
  for (int j = 0; j < N_sims; j++) {
    neuron.firing_rate(rate, time, *signal, adapt);

// Progress
#pragma omp critical
    {
      ++progbar;
      progbar.display();
    };
  };

  // print firing rate to file
  std::ofstream file;
  file.open(opts.get_output_file());

  double t = time.get_t_0();
  for (int i = 0; i < time.get_steps(); i++) {
    t += time.get_dt();
    file << t << "," << (double)rate[i] / N_sims << "\n";
  };

  progbar.done();
  file.close();

  return 0;
};
