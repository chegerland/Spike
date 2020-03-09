// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "StepSignal.h"

StepSignal::StepSignal(double alpha, double t_0) : alpha(alpha), t_0(t_0){};

StepSignal::StepSignal(std::string input_file) {

  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  std::string type = root.get<std::string>("Signal.type");
  assert(type == "step");

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  t_0 = root.get<double>("Signal.t_0");
};

double StepSignal::signal(double t) const {
  double result;

  if (t < t_0) {
    result = 0;
  } else {
    result = alpha;
  };

  return result;
}
