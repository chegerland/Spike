#include <iostream>

#include "Spike.h"

// main
int main(int argc, char *argv[])
{
  // define LIF neuron with adaptation and signal
  LIF lif(1.1, 0.001);
  ExpAdaptation adapt(0.005, 5);
  CosineSignal signal(0.05, 0.215);

  // define simulation time frame
  Timeframe time(0.0, 300.0, 1e-2);

  // array to put firing rate into
  std::vector<double> rate;

  // get firing rate
  int N = 100000;
  #pragma omp parallel for
  for (int j = 0; j < N; j++)
  {
    lif.firing_rate(rate, time, signal, adapt);
  };

  // print firing rate to std
  double t = time.get_t_0();
  for (int i = 0; i < time.get_steps(); i++)
  {
    t += time.get_dt();
    std::cout << t << " " << (double) rate[i]/N << std::endl;
  };



  return 0;
};
