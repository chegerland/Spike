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

// get spike times of an IF neuron
void IFadapt::spike_times(std::vector<double> &spikes, Simulation *simulation) const
{
  // initial values
  double v = 0;
  double a = this->Delta;
  double t = simulation->t_0;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(simulation->dt));

  while (t < simulation->t_end)
  {
    // update t, v and a
    t += simulation->dt;
    v += this->drift(v, t) * simulation->dt - a*simulation->dt + this->diffusion(v, t) * dist(generator);
    a += 1.0/this->tau_a *( -a)*simulation->dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += this->Delta;
      spikes.push_back(t);
    };

  };
};

// print voltage curve
void IFadapt::voltage_curve(Simulation *simulation) const
{
  // declare output file
  std::string output_file = simulation->spike_times_file.substr(0,simulation->spike_times_file.find_last_of('.'))+"_v_a_curve.out";
  std::ofstream curve_file;
  curve_file.open(output_file);

  // initial conditions
  double v = 0;
  double a = this->Delta;
  double t = simulation->t_0;
  curve_file << t << " " << v << " " << a << std::endl;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(simulation->dt));

  // run simulation
  while (t < simulation->t_end)
  {
    // update t, v and a
    t += simulation->dt;
    v += this->drift(v, t) * simulation->dt - a*simulation->dt + this->diffusion(v, t) * dist(generator);
    a += 1.0/this->tau_a *( -a)*simulation->dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += this->Delta;
    };

    // push t and v to file
    curve_file << t << " " << v << " " << a  << std::endl;
  };

  // close file
  curve_file.close();
};
