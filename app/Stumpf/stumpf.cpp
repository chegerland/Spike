#include <iostream>
#include <fstream>

#include "Spike.h"
#include "ProgressBar.hpp"

// main
int main(int argc, char *argv[])
{
  // define LIF neuron with adaptation and signal
  LIF lif(1.1, 0.001);
  CosineSignal signal(0.05, 0.215);
  ExpAdaptation adapt(0.126, 23.81);

  // define simulation time frame
  Timeframe time(0.0, 300.0, 1e-2);

  // array to put firing rate into
  std::vector<double> rate;
  rate.resize(time.get_steps());

  // get firing rate
  int N_sims = 100000;

  ProgressBar progbar(N_sims, 70);

  #pragma omp parallel for
  for (int j = 0; j < N_sims; j++)
  {
    lif.firing_rate(rate, time, signal, adapt);

    // Progress
    #pragma omp critical
    {
      ++progbar;
      progbar.display();
    };
  };

  // print firing rate to file

  // open filestream
  std::ofstream file;
  file.open("lif_adapt.txt");


  double t = time.get_t_0();
  for (int i = 0; i < time.get_steps(); i++)
  {
    t += time.get_dt();
    file << t << " " << (double) rate[i]/N_sims << "\n";
  };

  file.close();

  return 0;
};
