#include <iostream>

#include "Spike/Spike.h"

using namespace Spike;

int main(int argc, char *argv[]) {

  // define time frame
  TimeFrame tf(0.0, 1e4, 1e-3);
  SpikeTrain spike_train(tf);

  // define mu
  const double mu_start = 0.0;
  const double mu_end = 5.0;
  const double mu_step = 0.1;
  std::vector<double> mu((mu_end - mu_start) / mu_step);

  // define neurons
  std::array<LIFAC, 5> lifac_array = {
      LIFAC(1.1, 0.1, 5.0, 1e-1), LIFAC(1.1, 0.1, 5.0, 1e-1),
      LIFAC(1.1, 0.1, 5.0, 1e-1), LIFAC(1.1, 0.1, 5.0, 1e-1),
      LIFAC(1.1, 0.1, 5.0, 1e-1),
  };
  std::array<std::vector<double>, 5> rate_array = {
      std::vector<double>(mu.size()), std::vector<double>(mu.size()),
      std::vector<double>(mu.size()), std::vector<double>(mu.size()),
      std::vector<double>(mu.size()),
  };

  // step through all mu's
  for (size_t i = 0; i < mu.size(); i++) {
    // set new mu
    mu[i] = mu_start + i * mu_step;

    // for every neuron do
    for (size_t j = 0; j < lifac_array.size(); j++) {
      lifac_array[j].set_mu(mu[i]);

      // calculate spike train
      spike_train.clear();
      lifac_array[j].get_spikes(spike_train);

      // calculate rate
      rate_array[i][j] =
          spike_train.spike_count() / (tf.get_t_end() - tf.get_t_0());

      std::cout << mu[i] << "," << rate_array[i][j] << std::endl;
    }
  }

  return 0;
}