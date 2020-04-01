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

Neuron *NeuronFactory::create(const std::string &input_file) {
  // pointer to neuron
  Neuron *neuron = nullptr;

  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // read neuron type
  std::string type = root.get<std::string>("Neuron.type");

  // create appropriate neuron
  if (type == "PIF") {
    neuron = new PIF(input_file);
  } else if (type == "LIF") {
    neuron = new LIF(input_file);
  } else if (type == "PIFAC") {
    neuron = new PIFAC(input_file);
  } else if (type == "LIFAC") {
    neuron = new LIFAC(input_file);
  } else {
    std::cerr << "Error: Unknown Neuron type (" << type << ")!\n" << std::endl;
    exit(0);
  }

  // return neuron pointer
  return neuron;
}
