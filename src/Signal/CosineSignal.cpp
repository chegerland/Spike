#include <iostream>
#include <math.h>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "CosineSignal.h"

CosineSignal::CosineSignal(double alpha, double f) : alpha(alpha), f(f){};

CosineSignal::CosineSignal(std::string input_file) {
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f = root.get<double>("Signal.f");
};

double CosineSignal::signal(double t) {
  return alpha * cos(2.0 * M_PI * f * t);
};

// print parameters
void CosineSignal::print_parameters() {
  std::cout << "Signal (CosineSignal) parameters: \n"
            << "alpha = " << alpha << "\n"
            << "f = " << f << "\n"
            << std::endl;
};
