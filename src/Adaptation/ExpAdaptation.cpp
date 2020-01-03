// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "ExpAdaptation.h"

ExpAdaptation::ExpAdaptation(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read variables
  tau_a = root.get<double>("Adaptation.tau_a");
  assert(tau_a > 0);
  Delta = root.get<double>("Adaptation.Delta");
  assert(Delta > 0);
};

double ExpAdaptation::adapt(double a, double t)
{
  return -1.0/tau_a * a;
};

void ExpAdaptation::reset_rule(double a)
{
  a += Delta;
};
