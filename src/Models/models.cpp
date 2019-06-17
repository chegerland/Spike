#include <math.h>
#include <random>
#include <iostream>
#include <fstream>
#include "models.h"

/* Euler Maruyama
* - with fire and reset rule
* - without refractory time
* - returns time discretization and voltage 
*/
void voltageCurve(IF *neuron, std::vector<double> &t, std::vector<double> &v)
{

  /* initial values*/
  v.push_back(0);
  t.push_back(neuron->t_0);

  /* time step */
  double dt = (double)(neuron->t_end - neuron->t_0) / neuron->N;

  /* random numbers */
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  /* euler maruyama */
  double nextStep = 0;
  for (int i = 0; i < neuron->N - 1; i++)
  {
    t.push_back(t[i] + dt);
    nextStep = v[i] + neuron->drift(v[i], t[i]) * dt + neuron->diffusion(v[i], t[i]) * dist(generator);

    /* reset rule */
    if (nextStep > 1)
    {
      v.push_back(0);
    }
    else
    {
      v.push_back(nextStep);
    }
  }

};

/* get only the spike times */
void spikeTimes(IF *neuron, std::vector<double> &spikes)
{

  /* initial values*/
  double t;
  double v;
  v = 0;
  t = neuron->t_0;

  /* time step */
  double dt = (double)(neuron->t_end - neuron->t_0) / neuron->N;

  /* random numbers */
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  /* euler maruyama */
  double nextStep = 0;
  for (int i = 0; i < neuron->N - 1; i++)
  {
    t += dt;
    nextStep = v + neuron->drift(v, t) * dt + neuron->diffusion(v, t) * dist(generator);

    /* reset rule */
    if (v > 1)
    {
      v = 0;
      spikes.push_back(t);
    }
    else
    {
      v = nextStep;
    }
  }
};

/* get the spike train */
void spikeTrain(IF *neuron, std::vector<double> &spikes)
{

  /* initial values*/
  double t;
  double v;
  v = 0;
  t = neuron->t_0;

  /* time step */
  double dt = (double)(neuron->t_end - neuron->t_0) / neuron->N;

  /* random numbers */
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  /* euler maruyama */
  double nextStep = 0;
  for (int i = 0; i < neuron->N - 1; i++)
  {
    t += dt;
    nextStep = v + neuron->drift(v, t) * dt + neuron->diffusion(v, t) * dist(generator);

    /* reset rule */
    if (v > 1)
    {
      v = 0;
      spikes.push_back(1);
    }
    else
    {
      v = nextStep;
      spikes.push_back(0);
    }
  }
};

/* firing rate */
double firingRate(double t, const std::vector<double> &spikeTimes, double dt)
{

  double rate = 0;
  for (int i = 0; i < spikeTimes.size(); i++)
  {
    if (-dt / 2 <= (t - spikeTimes[i]) && (t - spikeTimes[i]) < dt / 2)
    {
      rate += 1 / dt;
    }
    else
    {
      rate += 0;
    }
  }

  return rate;
};

/*************
  INPUT OUTPUT
**************/

/* print vectors to standard output */
void toStdOut(const std::vector<double> &x, const std::vector<double> &y)
{
  /* check size of vectors */
  if (x.size() != y.size())
  {
    std::cout << "Output vectors do not have the same length!" << std::endl;
    exit(0);
  };

  for (int i = 0; i < x.size(); i++)
  {
    std::cout << x[i] << " " << y[i] << std::endl;
  };
};

/* print vectors to file */
void toCSV(char fileName[100], const std::vector<double> &x, const std::vector<double> &y)
{
  /* check size of vectors */
  if (x.size() != y.size())
  {
    std::cout << "Output vectors do not have the same length!" << std::endl;
    exit(0);
  };

  /* writes values to file */
  std::ofstream file;
  file.open(fileName);
  file << "t,v"
       << "\n";

  /* print values to file */
  for (int i = 0; i < x.size(); i++)
  {
    file << x[i] << "," << y[i] << "\n";
  };

  /* close file */
  file.close();
};