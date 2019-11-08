#include <vector>
#include <random>
#include <iostream>
#include <fstream>

#include "IFadapt.h"

// diffusion
double IFadapt::diffusion(double v, double t) const
{
  return sqrt(2*D);
};

void IFadapt::spike(std::vector<double> &spike_train, Timeframe *times) const
{
  // initial values
  double v = 0;
  double a = this->Delta;
  double t = times->t_0;

  // clear spike_train
  spike_train.clear();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(times->dt));

  while (t < times->t_end)
  {
    // update t, v and a
    t += times->dt;
    v += this->drift(v, t) * times->dt - a*times->dt + this->diffusion(v, t) * dist(generator);
    a += 1.0/this->tau_a *( -a)*times->dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += this->Delta;
      spike_train.push_back(t);
    };

  };
};


void IFadapt::spike(std::vector<double> &spike_train, Timeframe *times, Signal *signal) const
{
  // initial values
  double v = 0;
  double a = this->Delta;
  double t = times->t_0;

  // clear spike_train
  spike_train.clear();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(times->dt));

  while (t < times->t_end)
  {
    // update t, v and a
    t += times->dt;
    v += this->drift(v, t) * times->dt + signal->signal(t) - a*times->dt + this->diffusion(v, t) * dist(generator);
    a += 1.0/this->tau_a *( -a)*times->dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += this->Delta;
      spike_train.push_back(t);
    };

  };
};

// print voltage curve
void IFadapt::voltage_curve(std::vector<double> &curve_v, std::vector<double> &curve_a, Timeframe *times) const
{
  // initial conditions
  double v = 0;
  double a = this->Delta;
  double t = times->t_0;

  curve_v.clear();
  curve_v.push_back(v);
  curve_a.clear();
  curve_a.push_back(a);

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(times->dt));

  // run simulation
  while (t < times->t_end)
  {
    // update t, v and a
    t += times->dt;
    v += this->drift(v, t) * times->dt - a*times->dt + this->diffusion(v, t) * dist(generator);
    a += 1.0/this->tau_a *( -a)*times->dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += this->Delta;
    };

    curve_v.push_back(v);
    curve_a.push_back(a);

  };
};

// print voltage curve
void IFadapt::voltage_curve(std::vector<double> &curve_v, std::vector<double> &curve_a, Timeframe *times, Signal *signal) const
{
  // initial conditions
  double v = 0;
  double a = this->Delta;
  double t = times->t_0;

  curve_v.clear();
  curve_v.push_back(v);
  curve_a.clear();
  curve_a.push_back(a);

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(times->dt));

  // run simulation
  while (t < times->t_end)
  {
    // update t, v and a
    t += times->dt;
    v += this->drift(v, t) * times->dt + signal->signal(t) - a*times->dt + this->diffusion(v, t) * dist(generator);
    a += 1.0/this->tau_a *( -a)*times->dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += this->Delta;
    };

    curve_v.push_back(v);
    curve_a.push_back(a);

  };
};
