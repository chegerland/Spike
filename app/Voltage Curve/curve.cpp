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
  // define neuron
  IFadapt *neuron = new LIFadapt(3.0, 0.0001, 3.0, 2.0);
  Timeframe *times = new Timeframe(0.0, 40.0, 1e-3);

  // push voltage curve
  std::vector<double> curve_v;
  std::vector<double> curve_a;
  neuron->voltage_curve(curve_v, curve_a, times);

  std::ofstream file;
  file.open("voltage_curve.txt");

  for (int i = 0; i < curve_v.size(); i++)
  {
      file << curve_v[i] << " " << curve_a[i] << std::endl;
  };

  file.close();

  // limit cycle
  neuron->limit_cycle(curve_v, curve_a);

  std::ofstream file2;
  file2.open("limit_cycle.txt");

  for (int i = 0; i < curve_v.size(); i++)
  {
      file2 << curve_v[i] << " " << curve_a[i] << std::endl;
  };

  file2.close();

};
