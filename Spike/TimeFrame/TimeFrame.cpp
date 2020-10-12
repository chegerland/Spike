#include <cassert>

// ini parser
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

TimeFrame::TimeFrame(double t_0, double t_end, double dt)
    : t_0(t_0), t_end(t_end), dt(dt) {
  assert(t_end > t_0);
  assert(dt < t_end - t_0);

  // resize times vector
  t.resize((unsigned int)((t_end - t_0) / dt + 1));

  calculate_times();
}

TimeFrame::TimeFrame(const std::string &input_file) {
  // Create a root
  pt::ptree root;

  // Load the ini file in this ptree
  pt::read_ini(input_file, root);

  // read parameters
  t_0 = root.get<double>("TimeFrame.t_0");
  t_end = root.get<double>("TimeFrame.t_end");
  dt = root.get<double>("TimeFrame.dt");

  // check parameters
  assert(t_end > t_0);
  assert(dt < t_end - t_0);

  // calculate size
  t.resize((unsigned int)((t_end - t_0) / dt + 1));
  calculate_times();
}

void TimeFrame::calculate_times() {
  // fill time vector
  for (size_t i = 0; i < t.size(); i++) {
    t[i] = t_0 + i * dt;
  }
}

std::ostream &operator<<(std::ostream &out, const TimeFrame &tf) {
  out << "TimeFrame(t_0: " << tf.t_0 << ", t_end: " << tf.t_end
      << ", dt: " << tf.dt << ")";
  return out;
}

} // namespace Spike