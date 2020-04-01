#include <cmath>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "FiringRateExp.h"

FiringRateExp::FiringRateExp(const std::string &input_file,
                             const TimeFrame &time_frame)
    : FiringRate(time_frame) {

  // check if type is right
  pt::ptree root;
  pt::read_json(input_file, root);
  std::string type = root.get<std::string>("FiringRate.type");
  assert(type == "exponential");

  // read resolution
  res = root.get<double>("FiringRate.res");
  assert(res > 0);
}

FiringRateExp::FiringRateExp(const TimeFrame &time_frame, double res)
    : FiringRate(time_frame), res(res) {}

void FiringRateExp::calculate() {

  // compute the firing rate, that is for every position i calculate
  // 1/(sqrt(2*pi*res^2) * exp( (t_i - t_j)^2 / (2 * res^2) )
  // and multiply by the number of spikes at t_j
  double t_0, tau;
  for (int i = 0; i < time_frame.get_steps(); i++) {
    t_0 = time_frame.get_time(i);

    for (int j = 0; j < time_frame.get_steps(); j++) {
      if (spike_histogram[j] != 0) {
        tau = time_frame.get_time(j);
        values[i] += ((double)spike_histogram[j]) /
                     ((double)N_Neurons * sqrt(2.0 * M_PI) * res) *
                     exp(-(t_0 - tau) * (t_0 - tau) / (2.0 * res * res));
      }
    }
  }
}