#include <fstream>
#include <iostream>

#include "../../extern/ProgressBar.hpp"
#include "Spike.h"

// main
int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);
  std::string parameters = opts.get_parameter_file();

  // define neuron
  LIF lif(parameters);
  Timeframe time(parameters);

  // define adaptation
  ExpAdaptation adapt(parameters);
  int Delta_steps = 3;
  double Delta_vals[Delta_steps] = {1e-2, 1e-1, 1};

  // define mu scale
  double mu = 0.5;
  double mu_end = 5.;
  double dmu = 0.05;
  int muSteps = (int)((mu_end - mu) / dmu);

  // array to put mean rate into
  double rate[muSteps][Delta_steps];

  // define output file
  std::ofstream file;
  file.open(opts.get_output_file());

  ProgressBar progbar(muSteps, 70);

  // loop over mu values
  for (int i = 0; i < muSteps; i++) {

    // increase mu
    mu += dmu;
    lif.set_mu(mu);
    file << mu << ",";

    // calculate mean rate without adaptation
    file << (double)lif.count(time) / time.get_t_end() << ",";

    // calculate mean rate with adaptation
    for (int j = 0; j < Delta_steps; j++) {
      adapt.set_Delta(Delta_vals[j]);
      rate[i][j] = (double)lif.count(time, adapt) / time.get_t_end();
      file << rate[i][j] << ",";

      if (mu > 1.0) {
        file << 1.0 / (double)lif.limit_cycle_period(adapt) << ",";
      } else {
        file << 0 << ",";
      };
    };

    file << "\n";
    ++progbar;
    progbar.display();
  };

  // close file and progress bar
  progbar.done();
  file.close();

  return 0;
};
