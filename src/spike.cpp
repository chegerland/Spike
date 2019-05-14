#include "models.h"
#include <iostream>
#include <fstream>
#include <vector>


int main(int argc, char *argv[])
{

  // define new neuron with all parameters
  IF *P = new IF();
  P->t_0 = 0;
  P->t_end = 10;
  P->N = 1000;
  P->mu = 0.8;
  P->D = 0.01;

  /*
  // define and fill vectors
  std::vector<double> t;
  std::vector<double> v;
  em(P, t, v);

  // print vectors to file
  char fileName[100] = "../data/test.csv";
  toFile(fileName, t, v);
  */

  size_t Nsims = 10;
  std::vector<double> spikes;

  
  std::ofstream file;
  file.open("../data/spikeTimesTest.csv");

  // define time and rate vectors
  std::vector<double> t;
  std::vector<double> rate;

  t.push_back(P->t_0); // initial value
  rate.push_back(0); // initial value
  double dt = (double) (P->t_end - P->t_0 ) / P->N; // time step

  // fill in the right time
  // fill in zeros for the rate
  for (int j = 0; j < P->N; j++)
  {
    t.push_back(t[j]+dt);
    rate.push_back(0);
  }

  std::cout.precision(5);
  // loop over simulations
  //for (int i = 0; i < Nsims; i++)
  //{
    // generate spike train
    spikeTimes(P, spikes);

    // calculate firing rate
    for (int j = 0; j < P->N; j++)
    {
      rate[j] += 1*firingRate(t[j], spikes, dt);
      std::cout << rate[j] << std::endl;
    }
    // print spike times to file
    for (auto i = spikes.begin(); i != spikes.end(); ++i)
    {
      file << *i << ' ';
    }

    file << "\n";
  //  spikes.clear();
  //}

  file.close();

  //toStdOut(t, rate);

  return 0;
}