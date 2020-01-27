// ini parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "Signal.h"

Signal::Signal(){};

Signal::Signal(std::string input_file) {
  // Create a root
  pt::ptree root;

  // Load the ini file in this ptree
  pt::read_json(input_file, root);

  // read parameters
  this->type = root.get<std::string>("Signal.type");
}
