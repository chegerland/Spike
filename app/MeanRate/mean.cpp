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
  double mu_0 = root.get<double>("mu_0");
  double mu_end = root.get<double>("mu_end");
  double dmu = root.get<double>("dmu");
  int muStep = (int) (mu_end - mu_0) / dmu;

  double D = root.get<double>("D");

  // adaption
  double Delta = root.get<double>("Delta");
  double tau_a = root.get<double>("tau_a");

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

  std::cout << "Starting simulation." << std::endl;

  // define output files
  std::ofstream file;
  std::string name = options->file.substr(0,options->file.find_last_of('.'))+".out";
  file.open(name);

  for (int i = 0; i < muStep; i++)
  {
    // new mu
    double mu = mu_0 + i*dmu;

    // initial values
    double v = 0.0;
    double v_a = 0.0;
    double a = 0.0;
    double t = t_0;
    double r0 = 0.0;
    double r0_a = 0.0;

    // euler maruyama scheme
    for (int j = 0; j < Nsteps; j++)
    {
      // update time and voltage
      t += dt ;
      v += (mu - v) * dt + sqrt(2.0 * D)* dist(generator);
      v_a += (mu - v_a) * dt - a*dt + sqrt(2.0 * D)* dist(generator);
      a += 1.0/tau_a * (-a)*dt;

      // fire and reset rule
      if (v > 1)
      {
        v = 0;
        r0 += 1.0/(t_end - t_0);
      };

      // fire and reset for adaption
      if (v_a > 1)
      {
        v_a = 0;
        a += Delta;
        r0_a += 1.0/(t_end - t_0);
      };


    };

    file << mu << " " << r0 << " " << r0_a << "\n";
    std::cout << "Mu = " << mu << ", Mean rate: "  << r0 << " (" << r0_a << ")"<< std::endl;

  };

  file.close();

  exit(0);
};
