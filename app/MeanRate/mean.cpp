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
  int NDelta = 4;
  double tau_a = root.get<double>("tau_a");
  double Delta_list[NDelta] = {0.1, 1.0, 3.0, 10.0};

  // parameters
  double t_0 = root.get<double>("t_0");
  double t_end = root.get<double>("t_end");
  double dt = root.get<double>("dt");
  int Nsteps = (int) (t_end - t_0)/dt;

  std::cout << "Read data:" << std::endl;

  // rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  std::cout << "Starting simulation." << std::endl;

  // define output files
  std::ofstream file;
  std::string name = options->file.substr(0,options->file.find_last_of('.'))+".out";
  file.open(name);

  // without adaptation
  for (int i = 0; i < muStep; i++)
  {
    // new mu
    double mu = mu_0 + i*dmu;

    // initial values
    double v = 0.0;
    double t = t_0;
    double r0 = 0.0;

    // without adaptation
    for (int j = 0; j < Nsteps; j++)
    {
      // update time and voltage
      t += dt;
      v += (mu - v) * dt + sqrt(2.0 * D)* dist(generator);

      // fire and reset rule
      if (v > 1)
      {
        v = 0;
        r0 += 1.0/(t_end - t_0);
      };
    };
    file << mu << " " << r0;
    std::cout << mu << " " << r0;

    for (int k = 0; k < NDelta; k++)
    {
        // new tau_a
        double Delta = Delta_list[k];

        // initial values
        double v_a = 0.0;
        double a = 0.0;
        double t = t_0;
        double r0 = 0.0;

        // adaptation
        for (int l = 0; l < Nsteps; l++)
        {
            // update time and voltage
            t += dt ;
            v_a += (mu - v_a) * dt - a*dt + sqrt(2.0 * D)* dist(generator);
            a += 1.0/tau_a * (-a)*dt;

            // fire and reset for adaption
            if (v_a > 1)
            {
                v_a = 0;
                a += Delta;
                r0 += 1.0/(t_end - t_0);
            };
        };

        file << " " << r0;
        std::cout << " " << r0;
    };

    file << "\n";
    std::cout << std::endl;
  };

  file.close();

  exit(0);
};
