#include <iostream>

#include "Spike.h"

// main
int main(int argc, char *argv[])
{
  //Options options(argc, argv);

  // define neuron
  LIF lif(0.5, 0.001);
  Timeframe time(0.0, 1e4, 1e-2);

  // define adaptation
  ExpAdaptation adapt(3, 0.5);
  int Delta_steps = 3;
  double Delta_vals[Delta_steps] = {0.1, 1, 2, 10};

  // define mu steps
  double mu = 0.5;
  double mu_end = 3.5;
  double dmu = 0.01;
  int muSteps = (int) ((mu_end-mu)/dmu);

  // array to put mean rate into
  double rate[muSteps][Delta_steps];

  // loop over mu values
  for(int i = 0; i < muSteps; i++)
  {
    mu += dmu;
    lif.set_mu(mu);
    std::cout << mu << " " ;
    std::cout << (double) lif.count(time)/1e4 << " ";
    for(int j = 0; j < Delta_steps; j++)
    {
      adapt.set_Delta(Delta_vals[j]);
      rate[i][j] = (double) lif.count(time, adapt)/1e4;
      std::cout << rate[i][j] << " ";
    }
    std::cout << std::endl;
  }


  return 0;
};
