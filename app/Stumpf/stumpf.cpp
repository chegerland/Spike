#include <iostream>

#include "Spike.h"

// main
int main(int argc, char *argv[])
{
  // get command line options
  Options options(argc, argv);

  // define LIF neuron with adaptation
  LIF lif(options.file);
  Cosine signal(options.file);

  // define simulation time frame
  Timeframe time(0.0, 20.0, 1e-2);

  // array to put firing rate into
  double rate[time.steps] = { 0 };

  // get firing rate
  #pragma omp parallel for
  for (int j = 0; j < 100000; j++)
  {
    lif.firing_rate(rate, &time, &signal);
  };

  // print firing rate to std
  double t = time.t_0;
  for (int i = 0; i < time.steps; i++)
  {
    t += time.dt;
    std::cout << t << " " << 1e-5*rate[i] << std::endl;
  };



  return 0;
};
