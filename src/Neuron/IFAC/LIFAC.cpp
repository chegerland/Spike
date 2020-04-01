// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "LIFAC.h"
#include <random>
#include <iostream>

// constructor from parameters
LIFAC::LIFAC(double mu, double D, double tau_a, double Delta) : IFAC(mu, D, tau_a, Delta) {}

// constructor from input file
LIFAC::LIFAC(const std::string &input_file) : IFAC(input_file) {
  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  std::string type = root.get<std::string>("Neuron.type");
  assert(type == "LIFAC");
}

// drift of an LIFAC neuron
double LIFAC::drift(double v) const { return (this->mu - v); }

// get the spike train of an IFAC neuron with signal
void LIFAC::get_kernel(const TimeFrame &time, const Signal &signal,
                           const double norm, const int offset, double *kernel) const {
  // initial values
  double v = 0;
  double a = 0;

  // for better readibility
  double dt = time.get_dt();

  // initialize rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // perform euler maruyama scheme
  for (int i = 0; i < (int) time.get_steps(); i++) {
    v += (this->drift(v) - a + signal.get_value(i)) * dt +
         this->diffusion() * dist(generator);
    a += -1. / tau_a * a * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += Delta;
      for (int j = 0; j < i - offset; j++) {
        kernel[j] += norm * signal.get_value(i - j);
      }
    }
  }
}
