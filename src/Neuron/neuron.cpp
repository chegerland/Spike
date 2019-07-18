#include <iostream>
#include <random>

#include "neuron.h"

void IF::voltage_curve() const
{

  std::cout << "D = " << this->D << std::endl;
  std::cout << "mu = " << this->mu << std::endl;
};

void IF::spike_times(
    std::vector<double> &spikes)
{
  double v = 0;
  double t = this->t_0;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(this->dt));

  // euler maruyama scheme
  double next_step = 0;

  while (t < t_end)
  {
    t += dt;
    next_step = v + this->drift(v, t) * this->dt + this->diffusion(v, t) * dist(generator);

    if (v > 1) {
      v = 0;
      spikes.push_back(t);
    }
    else {
      v = next_step;
    }
  };
};

void simulation(neuron * neur, int N)
{
  std::vector<double> spikes;
  for (int i = 0; i < N; i++)
  {
    neur->spike_times(spikes);
  }

  for (int i = 0; i < spikes.size(); i++)
  {
    std::cout << spikes[i] << std::endl;
  }
};
