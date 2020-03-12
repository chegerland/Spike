// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "PIF.h"

// constructors
PIF::PIF(double mu, double D) : IF(mu, D){}

PIF::PIF(const std::string& input_file) : IF(input_file) {
  // check if type is right
  pt::ptree root;
  pt::read_json(input_file, root);
  std::string type = root.get<std::string>("Neuron.type");
  assert(type == "PIF");
}

// drift of a PIF neuron
double PIF::drift(double v, double t) const { return this->mu; }
