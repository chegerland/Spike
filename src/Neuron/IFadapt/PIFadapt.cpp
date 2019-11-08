#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "PIFadapt.h"

// constructor for a pif neuron
PIFadapt::PIFadapt(double a, double b, double c, double d)
{
  mu = a;
  D = b;
  Delta = c;
  tau_a = d;
};

// pif constructor from .json file
PIFadapt::PIFadapt(std::string input_file)
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

// drift of a PIF neuron
double PIFadapt::drift(double v, double t) const
{
  return mu;
};

// print neuron parameters
void PIFadapt::print_parameters() const
{
  std::cout << "Neuron (PIFadapt) parameters: \n"
  << "mu = "     << mu << "\n"
  << "D = "      << D << "\n"
  << "Delta = "     << Delta << "\n"
  << "tau_a = "      << tau_a << "\n"
  << std::endl;
};

// print limit limit_cycle
void PIFadapt::limit_cycle(std::vector<double> &curve_v, std::vector<double> &curve_a) const
{
  // calculate time period of limit cycle
  double period = 1.0/this->mu*(1 + this->Delta*this->tau_a);
  double fixed_point = this->Delta/(1.0 - exp(- period/this->tau_a));

  // time steps
  int steps = 1000;
  double dt = (double) period/steps;

  // initial values
  double t = 0;
  double a = fixed_point * exp(- t/this->tau_a);
  double v = this->mu*t - this->tau_a*fixed_point*(1.0 - exp(- t / this->tau_a));

  // clear vectors
  curve_v.clear();
  curve_v.push_back(v);
  curve_a.clear();
  curve_a.push_back(a);

  for (int i = 0; i < steps; i++)
  {
    // calculate new step
    t += dt;
    double a = fixed_point * exp(- t/this->tau_a);
    double v = this->mu*t - this->tau_a*fixed_point*(1.0 - exp(- t / this->tau_a));

    // push values to vectors
    curve_v.push_back(v);
    curve_a.push_back(a);
  };
};
