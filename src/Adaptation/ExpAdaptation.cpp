// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "ExpAdaptation.h"

ExpAdaptation::ExpAdaptation(double Delta, double tau_a)
    : Delta(Delta), tau_a(tau_a) {
  assert(Delta >= 0);
  assert(tau_a > 0);
}

ExpAdaptation::ExpAdaptation(const std::string& input_file) {

  // Load the json file into property tree
  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  std::string type = root.get<std::string>("Adaptation.type");
  assert(type == "exponential");

  // read variables
  tau_a = root.get<double>("Adaptation.tau_a");
  assert(tau_a > 0);

  Delta = root.get<double>("Adaptation.Delta");
  assert(Delta >= 0);
}

double ExpAdaptation::adapt(double a, double t) const {
  return -1.0 / tau_a * a;
}

double ExpAdaptation::reset_rule(double a) const { return a + Delta; }
