#include <cmath>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "CosineSignal.h"

// constructor from parameters
CosineSignal::CosineSignal(double alpha, double f,
                           const TimeFrame &time_frame)
    : Signal(time_frame), alpha(alpha), f(f) {
  calculate_signal();
}

// constructor from input file
CosineSignal::CosineSignal(const std::string &input_file,
                           const TimeFrame &time_frame)
    : Signal(time_frame) {

  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Signal.type");
  assert(type == "cosine");

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f = root.get<double>("Signal.f");

  // calculate the get_value values
  calculate_signal();
}

void CosineSignal::calculate_signal() {
  for (size_t i = 0; i < time_frame.get_steps(); i++) {
    signal_values[i] = alpha * cos(2.0 * M_PI * f * time_frame.get_time(i));
  }
}

// the get_value
double CosineSignal::signal(double t) const {
  return alpha * cos(2.0 * M_PI * f * t);
}

void CosineSignal::print_info(std::ofstream &file) const {
  file << "# Signal parameters: " << "\n"
       << "# type = " << "cosine" << "\n"
       << "# alpha = " << alpha << "\n"
       << "# f = " << f << "\n";
}
