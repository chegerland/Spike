#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "LIF.h"

// lif constructor
LIF::LIF(double a, double b)
{
  mu = a;
  D = b;
}

// lif constructor from .json
LIF::LIF(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  mu = root.get<double>("Neuron.mu");
  D = root.get<double>("Neuron.D");
};

// drift of an LIF neuron
double LIF::drift(double v, double t) const
{
  return (mu - v);
};

void LIF::print_parameters()
{
  std::cout << "Neuron (LIF) parameters: \n"
  << "mu = "     << mu << "\n"
  << "D = "      << D << "\n"
  << std::endl;
};
