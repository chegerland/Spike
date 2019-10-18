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
  options = new Options(argc, argv);

  /* Run a simulation
  // define simulation
  Simulation *simulation;
  simulation = new Simulation(options->file);

  //show parameters
  simulation->print_parameters();

  // run the simulation
  simulation->run();
  */

  /* print a voltage curve */
  LIF *lif;
  lif = new LIF(options->file);

  Timeframe *time;
  time = new Timeframe(0.0, 10.0, 1e-3);

  std::vector<double> voltages = lif->voltage_curve(time);

  for (int i = 0; i < voltages.size(); i++)
  {
      std::cout << voltages[i] << std::endl;
  };



};
