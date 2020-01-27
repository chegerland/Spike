// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "ExpAdaptation.h"

ExpAdaptation::ExpAdaptation(double Delta, double tau_a)
    : Delta(Delta), tau_a(tau_a) {
  assert(Delta >= 0);
  assert(tau_a > 0);
  this->type = "exponential";
};

ExpAdaptation::ExpAdaptation(std::string input_file) : Adaptation(input_file) {

  // check if type is right
  assert(this->type == "exponential");

  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read variables
  tau_a = root.get<double>("Adaptation.tau_a");
  assert(tau_a > 0);

  Delta = root.get<double>("Adaptation.Delta");
  assert(Delta >= 0);
};

double ExpAdaptation::adapt(double a, double t) { return -1.0 / tau_a * a; };

double ExpAdaptation::reset_rule(double a) { return a + Delta; };
