// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "Signal.h"

double Signal::signal(double t)
{
  return 0.0;
};

bool signal_given(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // check signal flag
  return root.get<bool>("signal");
};
