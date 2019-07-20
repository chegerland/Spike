#include <iostream>
#include <random>

#include "neuron.h"

/*!
 * SHOULD Return the voltage curve of a single neuron simulation.
 */
void IF::voltage_curve() const
{
  std::cout << "D = " << this->D << std::endl;
  std::cout << "mu = " << this->mu << std::endl;
};

/*!
 * Simulates the neuron and puts the spike times into the vector spikes
 * @param[in] spikes vector filled with the spike times
 */
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

/*!
 * Runs the simulation of a neuron N times.
 * @param[in] neuron the neuron to simulate
 * @param[in] N number of times the simulation shall be run
 */
void Neuron::simulation(int N)
{
  std::vector<double> spikes;
  for (int i = 0; i < N; i++)
  {
    this->spike_times(spikes);

    for (int i = 0; i < spikes.size(); i++)
    {
      std::cout << spikes[i] << std::endl;
    }

    std::cout << "" << std::endl;

    spikes.clear();
  }

};
