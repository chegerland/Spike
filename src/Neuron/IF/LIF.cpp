// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "LIF.h"
#include <iostream>

LIF::LIF(double mu, double D) : IF(mu, D) {}

LIF::LIF(const std::string &input_file) : IF(input_file) {
  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  std::string type = root.get<std::string>("Neuron.type");
  assert(type == "LIF");
}

double LIF::drift(double v) const { return (this->mu - v); }
