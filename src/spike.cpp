#include <iostream>
#include <vector>

#include "Neuron/neuron.h"

int main(int argc, char *argv[])
{
  IF pif_neuron;

  pif_neuron.t_0 = 0;
  pif_neuron.t_end = 7;
  pif_neuron.dt = 0.001;

  pif_neuron.mu = 1;
  pif_neuron.D = 2;

  //std::vector<double> spikes;

  //pif_neuron.spike_times(spikes);

  //for (int i = 0; i < spikes.size(); i++) {
  //  std::cout << spikes[i] << std::endl;
  //};

  simulation(&pif_neuron, 3);
}
