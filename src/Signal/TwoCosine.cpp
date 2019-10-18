#include <iostream>
#include <math.h>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "TwoCosine.h"

// TwoCosine constructor from .json
TwoCosine::TwoCosine(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  eps = root.get<double>("Signal.eps");
  alpha = root.get<double>("Signal.alpha");
  beta = root.get<double>("Signal.beta");
  phi = root.get<double>("Signal.phi");
  f1 = root.get<double>("Signal.f1");
  f2 = root.get<double>("Signal.f2");
};

double TwoCosine::signal(double t)
{
  return eps*(alpha*cos(2.0*M_PI*f1*t) + beta*cos(2.0*M_PI*f2*t+phi));
};

// print parameters
void TwoCosine::print_parameters()
{
  std::cout << "Signal (TwoCosine) parameters: \n"
  << "eps = "    << eps << "\n"
  << "alpha = "  << alpha << "\n"
  << "beta = "   << beta << "\n"
  << "phi = "    << phi << "\n"
  << "f1 = "     << f1 << "\n"
  << "f2 = "     << f2 << "\n"
  << std::endl;
};
