#include <cassert>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "TimeFrame.h"

TimeFrame::TimeFrame(double t_0, double t_end, double dt)
    : t_0(t_0), t_end(t_end), dt(dt) {
  assert(t_end > t_0);
  assert(dt < t_end - t_0);
  this->steps = (unsigned int)((t_end - t_0) / dt + 1);

  // resize times vector
  t.resize(steps);

  calculate_times();
}

TimeFrame::TimeFrame(const std::string &input_file) {
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read parameters
  t_0 = root.get<double>("TimeFrame.t_0");
  t_end = root.get<double>("TimeFrame.t_end");
  dt = root.get<double>("TimeFrame.dt");

  // check parameters
  assert(t_end > t_0);
  assert(dt < t_end - t_0);

  // calculate steps
  steps = (unsigned int)((t_end - t_0) / dt + 1);

  t.resize(steps);
  calculate_times();
}

void TimeFrame::calculate_times() {
  // fill time vector
  for (size_t i = 0; i < steps; i++) {
    t[i] = t_0 + i * dt;
  }
}

void TimeFrame::print_info(std::ofstream &file) {
  file << "# TimeFrame: "
       << "\n"
       << "# t_0 = " << t_0 << "\n"
       << "# t_end = " << t_end << "\n"
       << "# dt = " << dt << "\n";
}
