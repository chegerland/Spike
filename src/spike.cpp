#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <chrono>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

// spike libraries
#include "Spike.h"

// main
int main(int argc, char *argv[])
{
  // read command line options
  Options *options;
  options = new Options();
  get_options(argc, argv, options);

  // check the command line options
  check_options(options);

  Simulation *simulation;
  simulation = new Simulation(options->parameters);

  simulation->simulate();

};
