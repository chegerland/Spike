#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <assert.h>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "IF.h"

// constructor from file
IF::IF(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read parameters
  this->mu = root.get<double>("Neuron.mu");
  this->D = root.get<double>("Neuron.D");
};

// diffusion
double IF::diffusion(double v, double t) const
{
  return sqrt(2*D);
};

// count spikes of an IF neuron
int IF::count(Timeframe *time) const
{
  int count = 0;

  // initial values
  double v = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      count += 1;
    };
  };

  return count;
};

// count spikes of an IF neuron with signal
int IF::count(Timeframe *time, Signal *signal) const
{
  int count = 0;

  // initial values
  double v = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal->signal(t) * dt + diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      count += 1;
    };
  };

  return count;
};

// count spikes of an IF neuron with adaptation
int IF::count(Timeframe *time, Adaptation *adapt) const
{
  int count = 0;

  // initial values
  double v = 0;
  double a = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt - a * dt + diffusion(v, t) * dist(generator);
    a += adapt->adapt(a,t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      adapt->reset_rule(a);
      count += 1;
    };
  };

  return count;
};


// count spikes of an IF neuron with signal and adaptation
int IF::count(Timeframe *time, Signal *signal, Adaptation *adapt) const
{
  int count = 0;

  // initial values
  double v = 0;
  double a = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal->signal(t) * dt - a * dt + diffusion(v, t) * dist(generator);
    a += adapt->adapt(a,t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      adapt->reset_rule(a);
      count += 1;
    };
  };

  return count;
};


// calculate firing rate of an IF neuron
void IF::firing_rate(double* rate, Timeframe *time) const
{
  assert( sizeof(rate)/sizeof(double) == time->steps );

  // initial values
  double v = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      rate[i] += 1.0/dt;
    };
  };
};

// calculate firing rate of an IF neuron with signal
void IF::firing_rate(double* rate, Timeframe *time, Signal *signal) const
{
  assert( sizeof(rate)/sizeof(double) == time->steps );

  // initial values
  double v = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal->signal(t) * dt + diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      rate[i] += 1.0/dt;
    };
  };
};

// calculate firing rate of an IF neuron with adaptation
void IF::firing_rate(double* rate, Timeframe *time, Adaptation *adapt) const
{
  assert( sizeof(rate)/sizeof(double) == time->steps );

  // initial values
  double v = 0;
  double a = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt - a * dt + diffusion(v, t) * dist(generator);
    a += adapt->adapt(a,t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      adapt->reset_rule(a);
      rate[i] += 1.0/dt;
    };
  };
};

// calculate firing rate of an IF neuron with signal and adaptation
void IF::firing_rate(double* rate, Timeframe *time, Signal *signal, Adaptation *adapt) const
{
  assert( sizeof(rate)/sizeof(double) == time->steps );

  // initial values
  double v = 0;
  double a = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal->signal(t) * dt - a * dt + diffusion(v, t) * dist(generator);
    a += adapt->adapt(a,t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      adapt->reset_rule(a);
      rate[i] += 1.0/dt;
    };
  };
};

// voltage curve for IF
void IF::voltage_curve(double* v, Timeframe *time) const
{
  assert( sizeof(v)/sizeof(double) == time->steps );

  // initial values
  v[0] = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 1; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v[i] =  v[i-1] + this->drift(v[i-1], t) * dt + this->diffusion(v[i-1], t) * dist(generator);

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
    };
  };
};

// voltage curve for IF with adaptation
void IF::voltage_curve(double* v, double *a, Timeframe *time, Adaptation *adapt ) const
{
  assert( sizeof(v)/sizeof(double) == time->steps );
  assert( sizeof(a)/sizeof(double) == time->steps );

  // initial values
  v[0] = 0;
  a[0] = 0;
  double t = time->t_0;

  // for better readibility
  double dt = time->dt;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 1; i < time->steps; i++)
  {
    // update time and voltage
    t += dt;
    v[i] = v[i-1] + this->drift(v[i-1], t) * dt + this->diffusion(v[i-1], t) * dist(generator);
    a[i] = a[i-1] + adapt->adapt(a[i-1], t) * dt;

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
      adapt->reset_rule(a[i]);
    };
  };
};

// print the parameters
void IF::print_parameters() const
{
  std::cout << "Neuron (" << type << ") parameters: \n"
  << "mu = "     << mu << "\n"
  << "D = "      << D
  << std::endl;
};
