#include <cassert>
#include <iostream>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "Timeframe.h"

Timeframe::Timeframe(double t_0, double t_end, double dt)
    : t_0(t_0), t_end(t_end), dt(dt) {
  assert(t_end > t_0);
  assert(dt < t_end - t_0);
  this->steps = (int)((t_end - t_0) / dt);
};

Timeframe::Timeframe(std::string input_file) {
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read parameters
  t_0 = root.get<double>("Simulation.t_0");
  t_end = root.get<double>("Simulation.t_end");
  dt = root.get<double>("Simulation.dt");

  // check parameters
  assert(t_end > t_0);
  assert(dt < t_end - t_0);

  // calculate steps
  steps = (int)((t_end - t_0) / dt);
};

void Timeframe::print_parameters() {
  std::cout << "Time frame: \n"
            << "t_0 = " << t_0 << "\n"
            << "t_end = " << t_end << "\n"
            << "dt = " << dt << "\n"
            << std::endl;
};
