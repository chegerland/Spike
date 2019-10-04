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
void PIFadapt::print_parameters()
{
  std::cout << "Neuron (PIFadapt) parameters: \n"
  << "mu = "     << mu << "\n"
  << "D = "      << D << "\n"
  << "Delta = "     << Delta << "\n"
  << "tau_a = "      << tau_a << "\n"
  << std::endl;
};
