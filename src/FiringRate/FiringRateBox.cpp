// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "FiringRateBox.h"

FiringRateBox::FiringRateBox(const std::string &input_file,
                             const TimeFrame &time_frame)
    : FiringRate(time_frame) {

  // check if type is right
  pt::ptree root;
  pt::read_json(input_file, root);
  std::string type = root.get<std::string>("FiringRate.type");
  assert(type == "box");
}

FiringRateBox::FiringRateBox(const TimeFrame &time_frame)
    : FiringRate(time_frame){};

void FiringRateBox::calculate() {
  // divide appropriate spike histogram entry by N*dt
  for (int i = 0; i < time_frame.get_steps(); i++) {
    values[i] =
        1. / ((double)N_Neurons * time_frame.get_dt()) * spike_histogram[i];
  }
}