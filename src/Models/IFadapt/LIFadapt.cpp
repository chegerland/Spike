#include <iostream>
#include <math.h>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "LIFadapt.h"

// constructor for a lif neuron
LIFadapt::LIFadapt(double a, double b, double c, double d)
{
  mu = a;
  D = b;
  Delta = c;
  tau_a = d;
};

// lif constructor from .json file
LIFadapt::LIFadapt(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  mu = root.get<double>("Neuron.mu");
  D = root.get<double>("Neuron.D");
  Delta = root.get<double>("Neuron.Delta");
  tau_a = root.get<double>("Neuron.tau_a");
};

// drift of a LIF neuron
double LIFadapt::drift(double v, double t) const
{
  return (mu - v);
};

// print neuron parameters
void LIFadapt::print_parameters()
{
  std::cout << "Neuron (LIFadapt) parameters: \n"
  << "mu = "     << mu << "\n"
  << "D = "      << D << "\n"
  << "Delta = "     << Delta << "\n"
  << "tau_a = "      << tau_a << "\n"
  << std::endl;
};

// define function for root finding of limit cycle period
double LIFadapt::func(double x)
{
  return this->mu*(1.0 - exp(- x)) - this->Delta * 1.0/(1.0 - 1.0/this->tau_a)*(exp(-x/this->tau_a) - exp(-x))/(1.0 - exp(-x/this->tau_a)) - 1.0;
};

// calculate limit cycle period using bisection
double LIFadapt::limit_cycle_period(double x_lo, double x_hi, double epserr, int max_iter)
{
  double err = fabs(x_lo - x_hi)/2.0;

  // check sign
  if ( signbit(this->func(x_lo)) == signbit(this->func(x_hi)) )
  {
    std::cout << "Same sign!" << std::endl;
    exit(0);
  }

  int j = 0;
  double x = 0;
  double y = 0;
  while (j <= max_iter)
  {
      x = 0.5*(x_lo + x_hi);
      y = this->func(x);

      if (y == 0 || fabs(x_hi - x_lo)/2.0 < epserr)
      {
        break;
      }

      if ( signbit(y) == signbit(this->func(x_lo)) )
      {
        x_lo = x;
      }
      else
      {
        x_hi = x;
      };

      // next iteration
      j += 1;
  };

  return x;

};

// limit cycle
void LIFadapt::limit_cycle(Simulation *simulation)
{
  // declare output file
  std::string output_file = simulation->spike_times_file.substr(0,simulation->spike_times_file.find_last_of('.'))+"_limit_cycle.out";
  std::ofstream cycle_file;
  cycle_file.open(output_file);

  // get period
  double period = limit_cycle_period(1e-5, 100, 1e-5, 200);

  // calculate fixed point, i.e. adaption variable at peaking
  double fixed_point = this->Delta/(1.0 - exp(- period/this->tau_a));

  // time steps
  int steps = 1000;
  double dt = (double) period/steps;

  // initial values
  double t = 0;
  double a = fixed_point * exp(- t/this->tau_a);
  double v = this->mu*(1.0 - exp(-t)) - fixed_point * 1.0/(1.0 - 1.0/this->tau_a)*(exp(-t/this->tau_a) - exp(-t));

  cycle_file << t << " " << v << " " << a << std::endl;

  for (int i = 0; i < steps; i++)
  {
    // calculate new step
    t += dt;
    double a = fixed_point * exp(- t/this->tau_a);
    double v = this->mu*(1.0 - exp(-t)) - fixed_point * 1.0/(1.0 - 1.0/this->tau_a)*(exp(-t/this->tau_a) - exp(-t));

    // push values to file
    cycle_file << t << " " << v << " " << a << std::endl;
  };

  // close file
  cycle_file.close();
};
