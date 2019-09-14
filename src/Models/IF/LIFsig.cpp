#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "LIFsig.h"

// lifsig constructor from .json
LIFsig::LIFsig(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  mu = root.get<double>("Neuron.mu");
  D = root.get<double>("Neuron.D");
  eps = root.get<double>("Neuron.eps");
  alpha = root.get<double>("Neuron.alpha");
  beta = root.get<double>("Neuron.beta");
  phi = root.get<double>("Neuron.phi");
  f1 = root.get<double>("Neuron.f1");
  f2 = root.get<double>("Neuron.f2");
};

// drift of a lif neuron with signal
double LIFsig::drift(double v, double t) const
{
  return (mu - v + eps*(alpha*cos(2.0*M_PI*f1*t) + beta*cos(2.0*M_PI*f2*t+phi)));
};

// print neuron parameters
void LIFsig::print_parameters()
{
  std::cout << "Neuron (LIFsig) parameters: \n"
  << "mu = "     << mu << "\n"
  << "D = "      << D << "\n"
  << "eps = "    << eps << "\n"
  << "alpha = "  << alpha << "\n"
  << "beta = "   << beta << "\n"
  << "phi = "    << phi << "\n"
  << "f1 = "     << f1 << "\n"
  << "f2 = "     << f2 << "\n"
  << std::endl;
};
