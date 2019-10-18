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
void IF::spike_times(std::vector<double> &spikes, Simulation *simulation) const
{
  // initial values
  double v = 0;
  double t = simulation->t_0;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(simulation->dt));

  // euler maruyama scheme
  while (t < simulation->t_end)
  {
    // update time and voltage
    t += simulation->dt;
    v += this->drift(v, t) * simulation->dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spikes.push_back(t);
    };
  };
};

// get spike times of an IF neuron
void IF::spike_times(std::vector<double> &spikes, Simulation *simulation, Signal *signal) const
{
  // initial values
  double v = 0;
  double t = simulation->t_0;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(simulation->dt));

  // euler maruyama scheme
  while (t < simulation->t_end)
  {
    // update time and voltage
    t += simulation->dt;
    v += this->drift(v, t) * simulation->dt + signal->signal(t) * simulation->dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spikes.push_back(t);
    };
  };
};

// print voltage curve
void IF::voltage_curve(Simulation *simulation) const
{
  // declare output file
  std::string output_file = simulation->spike_times_file.substr(0,simulation->spike_times_file.find_last_of('.'))+"_v_curve.out";
  std::ofstream curve_file;
  curve_file.open(output_file);

  // initial conditions
  double v = 0;
  double t = simulation->t_0;
  curve_file << t << " " << v << std::endl;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(simulation->dt));

  // run simulation (euler maruyama scheme)
  while (t < simulation->t_end)
  {
    // update t and v
    t += simulation->dt;
    v += this->drift(v, t) * simulation->dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
    };

    // push t and v to file
    curve_file << t << " " << v << std::endl;
  };

  // close file
  curve_file.close();
};
