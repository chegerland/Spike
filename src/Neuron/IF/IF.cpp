#include <vector>
#include <random>
#include <iostream>
#include <fstream>

#include "IF.h"

// diffusion
double IF::diffusion(double v, double t) const
{
  return sqrt(2*D);
};

// get spike times of an IF neuron
void IF::spike(std::vector<double> &spike_train, Timeframe *times) const
{
  // initial values
  double v = 0;
  double t = times->t_0;

  // clear spike_train
  spike_train.clear();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(times->dt));

  // euler maruyama scheme
  while (t < times->t_end)
  {
    // update time and voltage
    t += times->dt;
    v += this->drift(v, t) * times->dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train.push_back(t);
    };
  };

};

// get spike times of an IF neuron
void IF::spike(std::vector<double> &spike_train, Timeframe *times, Signal *signal) const
{
  // initial values
  double v = 0;
  double t = times->t_0;

  // clear spike_train
  spike_train.clear();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(times->dt));

  // euler maruyama scheme
  while (t < times->t_end)
  {
    // update time and voltage
    t += times->dt;
    v += this->drift(v, t) * times->dt + signal->signal(t) * times->dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train.push_back(t);
    };
  };
};

// print voltage curve

std::vector<double> IF::voltage_curve(Timeframe *times) const
{

  // initial conditions
  double v = 0;
  double t = times->t_0;

  // vector for voltage values
  std::vector<double> voltage;
  voltage.push_back(v);

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(times->dt));

  // run simulation (euler maruyama scheme)
  while (t < times->t_end)
  {
    // update t and v
    t += times->dt;
    v += this->drift(v, t) * times->dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
    };

    // push voltage to vector
    voltage.push_back(v);

  };

  return voltage;
};
