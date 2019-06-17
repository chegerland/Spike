#include "Models/models.h"
#include <iostream>
#include <fstream>
#include <ctime> 
#include <vector>

/*
  produces the firing rate plots of a perfect IF neuron shown in the neusig lecture
  (Lecture 7)
*/
void pifNeusig()
{

  // define the PIF neuron with parameters shown on slide
  IF *P = new IF();
  P->t_0 = 0;
  P->t_end = 8;
  P->N = 1000;
  P->mu = 1;
  P->D = 0.02;

  // define vector vor spiketimes, time and firing rate
  std::vector<double> spikes;
  std::vector<double> t;
  std::vector<double> rate;

  // define time scale for firing rate
  int N = 400;
  double dt = (double)(P->t_end - P->t_0) / N; // time step

  // initial values
  t.push_back(P->t_0);
  rate.push_back(0);

  /* fill time and firing rate vector */
  for (int j = 0; j < N; j++)
  {
    t.push_back(t[j] + dt);
    rate.push_back(0);
  }

  /* loop over simulation */
  int Nsims = 10000;
  //clock_t begin = clock();
  for (int i = 0; i < Nsims; i++)
  {
    // get spike times
    spikeTimes(P, spikes);

    // get firing rate for every time step, weighted with 1/Nsims
    for (int j = 0; j < N; j++)
    {
      rate[j] += (double) 1.0 / Nsims * firingRate(t[j], spikes, 0.05);
    };

    // empty the spikes vector for next simulation run
    spikes.clear();
  }

  /* 
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Simulating "
            << Nsims
            << " neurons took "
            << elapsed_secs 
            << " seconds." << std::endl;
  */
  // print out time and rate 
  toStdOut(t, rate);
}

int main(int argc, char *argv[])
{
  // define new neuron with all parameters
  IF *P = new LIFsig();
  P->t_0 = 0;
  P->t_end = 15;
  P->N = 1000;
  P->mu = 1.1;
  P->D = 0.001;
  P->eps = 0.05;
  P->f = 0.215;

  /* input routine */
  if (argc == 1)
  {
    std::cout << "No arguments passed!" << std::endl;
    exit(0);
  }
  else
  {
    std::string argv1 = argv[1];

    // print curve to file
    if (argv1 == "curveCSV")
    {
      std::vector<double> t;
      std::vector<double> v;
      voltageCurve(P, t, v);

      char fileName[100] = "../data/test.csv";
      toCSV(fileName, t, v);
    }
    // print curve to standard output
    else if (argv1 == "curveStd")
    {
      std::vector<double> t;
      std::vector<double> v;
      voltageCurve(P, t, v);

      toStdOut(t, v);
    }
    // produce firing rate from the neusig lecture
    else if (argv1 == "pifNeusig")
    {
      pifNeusig();
    } else {

      // define vector vor spiketimes, time and firing rate
      std::vector<double> spikes;
      std::vector<double> t;
      std::vector<double> rate;

      // define time scale for firing rate
      int N = 1500;
      double dt = (double)(P->t_end - P->t_0) / N; // time step

      // initial values
      t.push_back(P->t_0);
      rate.push_back(0);

      /* fill time and firing rate vector */
      for (int j = 0; j < N; j++)
      {
        t.push_back(t[j] + dt);
        rate.push_back(0);
      }

      /* loop over simulation */
      int Nsims = 100000;
      for (int i = 0; i < Nsims; i++)
      {
        // get spike times
        spikeTimes(P, spikes);

        // get firing rate for every time step, weighted with 1/Nsims
        for (int j = 0; j < N; j++)
        {
          rate[j] += (double)1.0 / Nsims * firingRate(t[j], spikes, 0.1);
        };

        // empty the spikes vector for next simulation run
        spikes.clear();
      }

      // print out time and rate
      toStdOut(t, rate);
    }
  } 

  return 0;
}
