#include <iostream>
#include <memory>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "FiringRateBox.h"
#include "FiringRateExp.h"
#include "FiringRateFactory.h"

std::unique_ptr<FiringRate>
FiringRateFactory::create(const std::string &input_file,
                          const TimeFrame &time_frame) {

  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  std::string type = root.get<std::string>("FiringRate.type");

  if (type == "box") {
    return std::make_unique<FiringRateBox>(input_file, time_frame);
  } else if (type == "exponential") {
    return std::make_unique<FiringRateExp>(input_file, time_frame);
  } else {
    std::cerr << "Error: Unknown firing_rate type (" << type << ")!\n"
              << std::endl;
    exit(0);
  }
}