// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "Timeframe.h"

Timeframe::Timeframe(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read parameters
  t_0 = root.get<double>("Simulation.t_0");
  t_end = root.get<double>("Simulation.t_end");
  dt = root.get<double>("Simulation.dt");
};
