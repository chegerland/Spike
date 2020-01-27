#include <iostream>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "CosineSignal.h"
#include "TwoCosineSignal.h"

#include "SignalFactory.h"

Signal *SignalFactory::create(std::string input_file) {
  Signal *signal = NULL;

  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  std::string type = root.get<std::string>("Signal.type");

  if (type == "two cosine") {
    signal = new TwoCosineSignal(input_file);
  } else if (type == "cosine") {
    signal = new CosineSignal(input_file);
  } else {
    std::cerr << "Error: Unknown Signal type (" << type << ")!\n" << std::endl;
    exit(0);
  };

  return signal;
};
