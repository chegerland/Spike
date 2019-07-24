#include <iostream>
#include <vector>

#include "Neuron/neuron.h"

int main(int argc, char *argv[])
{
  LIF pif_neuron;

  double t_0 = 0;
  double t_end = 10.1;
  double dt = 1e-6;

  double mu = 0.2;
  double D = 4;

  pif_neuron.set_simulation_params(t_0, t_end, dt);
  pif_neuron.set_if_params(mu, D);

  std::vector<double> spikes;
  pif_neuron.spike_times(spikes);

  double rate = 1.0/(sqrt(M_PI*2*D/pow(mu-1, 2))*exp(pow(mu-1, 2)/(2*D)));
  int spike_count = (int) (rate*(t_end - t_0));


  std::cout << rate << std::endl;
  std::cout << spike_count << std::endl;
  std::cout << spikes.size() << std::endl;


}
