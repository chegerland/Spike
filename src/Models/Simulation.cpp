#include <iostream>

#include "Simulation.h"

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

// simulation constructor
// if no N is given, set N to 1
Simulation::Simulation(double a, double b, double c)
{
  t_0 = a;
  t_end = b;
  dt = c;
  N = 1;
};

// simulation constructor
Simulation::Simulation(double a, double b, double c, int d)
{
  t_0 = a;
  t_end = b;
  dt = c;
  N = d;
};

// constructor from file
Simulation::Simulation(std::string parameters_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(parameters_file, root);

  // read simulation data into simulation variables
  t_0 = root.get<double>("Simulation.t_0");
  t_end = root.get<double>("Simulation.t_end");
  dt = root.get<double>("Simulation.dt");
  N = root.get<int>("Simulation.N");

  // set output file
  spike_times_file = parameters_file.substr(0,parameters_file.find_last_of('.'))+".out";
};

// print parameters to standard output
void Simulation::print_parameters()
{
  std::cout << "Simulation parameters: \n"
  << "t_0 = "    << t_0 << "\n"
  << "t_end = "  << t_end << "\n"
  << "dt = "     << dt << "\n"
  << "N = "      << N << "\n"
  << std::endl;
};
