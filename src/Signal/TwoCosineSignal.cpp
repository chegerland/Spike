#include <iostream>
#include <math.h>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "TwoCosineSignal.h"

// constructor from parameters
TwoCosineSignal::TwoCosineSignal(double alpha, double f1, double beta,
                                 double f2, double phi)
    : alpha(alpha), f1(f1), beta(beta), f2(f2), phi(phi){};

// constructor from input file
TwoCosineSignal::TwoCosineSignal(std::string input_file) {

  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  std::string type = root.get<std::string>("Signal.type");
  assert(type == "two cosine");

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f1 = root.get<double>("Signal.f1");
  beta = root.get<double>("Signal.beta");
  f2 = root.get<double>("Signal.f2");
  phi = root.get<double>("Signal.phi");
};

// the signal
double TwoCosineSignal::signal(double t) const {
  return alpha * cos(2.0 * M_PI * f1 * t) +
         beta * cos(2.0 * M_PI * f2 * t + phi);
};
