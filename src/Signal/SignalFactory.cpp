#include <iostream>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "CosineSignal.h"
#include "SignalFactory.h"
#include "StepSignal.h"
#include "TwoCosineSignal.h"
#include "WhiteNoiseSignal.h"

// create get_value pointer
std::unique_ptr<Signal>
SignalFactory::create(const std::string &input_file,
                      const std::shared_ptr<const TimeFrame> &time_frame) {
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  std::string type = root.get<std::string>("Signal.type");

  if (type == "two cosine") {
    return std::make_unique<TwoCosineSignal>(input_file, time_frame);
  } else if (type == "cosine") {
    return std::make_unique<CosineSignal>(input_file, time_frame);
  } else if (type == "step") {
    return std::make_unique<StepSignal>(input_file, time_frame);
  } else if (type == "white noise") {
    return std::make_unique<WhiteNoiseSignal>(input_file, time_frame);
  } else {
    std::cerr << "Error: Unknown Signal type (" << type << ")!\n" << std::endl;
    exit(0);
  }
}
