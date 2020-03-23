// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "PIFAC.h"

// constructor from parameters
PIFAC::PIFAC(double mu, double D, double tau_a, double Delta)
    : IFAC(mu, D, tau_a, Delta) {}

// constructor from input file
PIFAC::PIFAC(const std::string &input_file) : IFAC(input_file) {
  // check if type is right
  pt::ptree root;
  pt::read_json(input_file, root);
  std::string type = root.get<std::string>("Neuron.type");
  assert(type == "PIFAC");
}

// drift of a PIFAC neuron
double PIFAC::drift(double v) const { return this->mu; }
