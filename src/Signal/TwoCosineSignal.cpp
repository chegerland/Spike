#include <iostream>
#include <math.h>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "TwoCosineSignal.h"

TwoCosineSignal::TwoCosineSignal(double alpha, double f1, double beta,
                                 double f2, double phi)
    : alpha(alpha), f1(f1), beta(beta), f2(f2), phi(phi) {
  this->type = "two cosine";
};

TwoCosineSignal::TwoCosineSignal(std::string input_file) : Signal(input_file) {
  // check if type is right
  assert(this->type == "two cosine");

  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f1 = root.get<double>("Signal.f1");
  beta = root.get<double>("Signal.beta");
  f2 = root.get<double>("Signal.f2");
  phi = root.get<double>("Signal.phi");
};

double TwoCosineSignal::signal(double t) {
  return alpha * cos(2.0 * M_PI * f1 * t) +
         beta * cos(2.0 * M_PI * f2 * t + phi);
};

// print parameters
void TwoCosineSignal::print_parameters() {
  std::cout << "Signal (TwoCosineSignal) parameters: \n"
            << "alpha = " << alpha << "\n"
            << "beta = " << beta << "\n"
            << "phi = " << phi << "\n"
            << "f1 = " << f1 << "\n"
            << "f2 = " << f2 << "\n"
            << std::endl;
};
