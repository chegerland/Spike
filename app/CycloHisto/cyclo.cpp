#include <math.h>
#include <random>
#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "ProgressBar.hpp"

#include "Spike.h"

// main
int main(int argc, char *argv[])
{

  Options *options;
  options = new Options(argc, argv);

  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(options->file, root);

  // neuron parameters
  double mu = root.get<double>("mu");
  double D = root.get<double>("D");

  // adaption
  double Delta = root.get<double>("Delta");
  double tau_a = root.get<double>("tau_a");

  // signal parameters
  double eps = root.get<double>("eps");
  double alpha = root.get<double>("alpha");
  double f1 = root.get<double>("f1");

  // parameters
  double t_0 = root.get<double>("t_0");
  double t_end = root.get<double>("t_end");
  double dt = root.get<double>("dt");
  int Nsteps = (int) (t_end - t_0)/dt;

  std::cout << "Read data." << std::endl;

  // rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // length of one period
  int period = (int) (1.0/(f1 * dt));
  int num_periods = Nsteps/period;
  double *rate = new double[period];

  std::cout << "Starting simulation." << std::endl;

  // define output files
  std::ofstream file;
  std::string name = options->file.substr(0,options->file.find_last_of('.'))+".out";
  file.open(name);

  // initial values
  double v = 0.0;
  double t = t_0;
  //double a = 0.0;

  // euler maruyama scheme
  for (int j = 0; j < Nsteps; j++)
  {
      // update time and voltage
      t += dt;
      //v += (mu - v) * dt - a*dt + eps*alpha*cos(2.0 * M_PI * f1 * t) * dt +  sqrt(2.0 * D)* dist(generator);
      v += (mu - v) * dt + eps*alpha*cos(2.0 * M_PI * f1 * t) * dt +  sqrt(2.0 * D)* dist(generator);
      //a += 1.0/tau_a *( -a)*dt;

      // fire and reset rule
      if (v > 1)
      {
          v = 0;
       //   a += Delta;
          rate[j % period] += 1.0/( num_periods * dt );
      };
  };

  // write rate to file
  std::cout << "Writing data to file." << std::endl;
  t = t_0;
  for (int k = 0; k < period; k++)
  {
    t += dt;
    file << t << " " << rate[k] << "\n";
  };

  file.close();

  delete[] rate;

  exit(0);
};
