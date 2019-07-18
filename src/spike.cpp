#include <iostream>
#include <vector>

#include "Neuron/neuron.h"

int main(int argc, char *argv[])
{
  LIF pif_neuron;

  pif_neuron.t_0 = 0;
  pif_neuron.t_end = 10.1;
  pif_neuron.dt = 1e-6;

  pif_neuron.mu = 0.2;
  pif_neuron.D = 4;

  std::vector<double> spikes;
  pif_neuron.spike_times(spikes);

  double rate = 1.0/(sqrt(M_PI*2*pif_neuron.D/pow(pif_neuron.mu-1, 2))*exp(pow(pif_neuron.mu-1, 2)/(2*pif_neuron.D)));
  int spike_count = (int) (rate*(pif_neuron.t_end - pif_neuron.t_0));


  std::cout << rate << std::endl;
  std::cout << spike_count << std::endl;
  std::cout << spikes.size() << std::endl;


}
