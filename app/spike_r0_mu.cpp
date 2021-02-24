#include <fstream>
#include <iostream>

#include "Spike/Spike.h"

using namespace Spike;

int main(int argc, char *argv[]) {

  // define time frame
  const TimeFrame tf(0.0, 1e4, 1e-3);
  SpikeTrain spike_train(tf);

  // define mu
  const double mu_start = 0.0;
  const double mu_end = 5.0;
  const double mu_step = 0.1;
  std::vector<double> mu((mu_end - mu_start) / mu_step);

  // define neurons
  LIFAC lifac(5.1, 0.1, 5.0, 1e-1);

  // define parameter values
  //const std::array<double, 5> tau_a = {1e-2, 1e-1, 1.0, 5.0, 10.0};
  const std::array<double, 5> Delta = {1e-2, 1e-1, 1.0, 5.0, 10.0};

  // array for firing rate
  std::vector<double> firing_rate(mu.size());

  // define output file
  std::ofstream file;
  //file.open("../data/r0_mu_tau_a_lifac.csv");
  file.open("../data/r0_mu_Delta_lifac.csv");
  file << "# Stationary firing rate for different values of mu\n";
  file << "# LIFAC(mu, D = 0.1, tau=5.0, Delta)";
  file << "# Delta = 1e-2, 1e-1, 1.0, 5.0, 10.0";
  file << "# mu, r0, ...\n";


  // step through the mu array
  for (size_t i = 0; i < mu.size(); i++) {
    // set new mu
    mu[i] = mu_start + i * mu_step;
    lifac.set_mu(mu[i]);
    std::cout << mu[i] << ",";
    file << mu[i] << ",";

    // for every neuron do
    for (size_t j = 0; j < Delta.size(); j++) {
      lifac.set_Delta(Delta[j]);

      // calculate spike train
      spike_train.clear();
      lifac.get_spikes(spike_train);

      // calculate rate
      firing_rate[i] =
          (double) (spike_train.spike_count() / (tf.get_t_end() - tf.get_t_0()));

      // print to cout and file
      std::cout << firing_rate[i];
      file << firing_rate[i];
      if (j < Delta.size() - 1) {
        std::cout << ",";
        file << ",";
      } else {
        std::cout << std::endl;
        file << std::endl;
      }
    }
  }

  file.close();

  return 0;
}