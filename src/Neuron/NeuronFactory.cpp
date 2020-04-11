#include <iostream>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "IF/LIF.h"
#include "IF/PIF.h"
#include "IFAC/LIFAC.h"
#include "IFAC/PIFAC.h"
#include "NeuronFactory.h"

std::unique_ptr<Neuron> NeuronFactory::create(const std::string &input_file) {
  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // read neuron type
  std::string type = root.get<std::string>("Neuron.type");

  // create appropriate neuron
  if (type == "PIF") {
    return std::make_unique<PIF>(input_file);
  } else if (type == "LIF") {
    return std::make_unique<LIF>(input_file);
  } else if (type == "PIFAC") {
    return std::make_unique<PIFAC>(input_file);
  } else if (type == "LIFAC") {
    return std::make_unique<LIFAC>(input_file);
  } else {
    std::cerr << "Error: Unknown Neuron type (" << type << ")!\n" << std::endl;
    exit(0);
  }
}
