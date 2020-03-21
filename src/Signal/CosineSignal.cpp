#include <iostream>
#include <math.h>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "CosineSignal.h"

// constructor from parameters
CosineSignal::CosineSignal(double alpha, double f) : alpha(alpha), f(f){};

// constructor from input file
CosineSignal::CosineSignal(std::string input_file) {

  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  std::string type = root.get<std::string>("Signal.type");
  assert(type == "cosine");

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f = root.get<double>("Signal.f");
};

// the signal
double CosineSignal::signal(double t) const {
  return alpha * cos(2.0 * M_PI * f * t);
};
