#include <iostream>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "FiringRateBox.h"
#include "FiringRateExp.h"
#include "FiringRateFactory.h"

FiringRate * FiringRateFactory::create(const std::string &input_file, const TimeFrame &time_frame) {
  FiringRate *firing_rate = nullptr;

  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  std::string type = root.get<std::string>("FiringRate.type");

  if (type == "box") {
    firing_rate = new FiringRateBox(input_file, time_frame);
  } else if (type == "exponential") {
    firing_rate = new FiringRateExp(input_file, time_frame);
  } else {
    std::cerr << "Error: Unknown FiringRate type (" << type << ")!\n" << std::endl;
    exit(0);
  }

  return firing_rate;
}