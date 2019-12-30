#include <iostream>
#include <math.h>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "Cosine.h"

// TwoCosine constructor from .json
Cosine::Cosine(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f = root.get<double>("Signal.f");
};

double Cosine::signal(double t)
{
  return alpha*cos(2.0*M_PI*f*t);
};

// print parameters
void Cosine::print_parameters()
{
  std::cout << "Signal (Cosine) parameters: \n"
  << "alpha = "  << alpha << "\n"
  << "f = "     << f << "\n"
  << std::endl;
};
