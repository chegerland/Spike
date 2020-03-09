// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "LIF.h"
#include <iostream>

// constructors
LIF::LIF(double mu, double D) : IF(mu, D){};

LIF::LIF(std::string input_file) : IF(input_file) {
  // check if type is right
  pt::ptree root;
  pt::read_json(input_file, root);
  std::string type = root.get<std::string>("Neuron.type");
  assert(type == "LIF");
};

// drift of an LIF neuron
double LIF::drift(double v, double t) const { return (this->mu - v); };

double LIF::func(ExpAdaptation &adapt, double x) {
  return mu * (1.0 - exp(-x)) -
         adapt.get_Delta() * adapt.get_tau_a() / (adapt.get_tau_a() - 1.0) *
             (exp(-x / adapt.get_tau_a()) - exp(-x)) /
             (1.0 - exp(-x / adapt.get_tau_a())) -
         1.0;
};

// calculate limit cycle period using bisection
double LIF::limit_cycle_period(ExpAdaptation &adapt) {
  double x_lo = 1e-4;
  double x_hi = 1e4;
  double epserr = 1e-7;
  int max_iter = 1e3;

  // check sign
  if (signbit(this->func(adapt, x_lo)) == signbit(this->func(adapt, x_hi))) {
    std::cout << "Same sign!" << mu << std::endl;
    exit(0);
  }

  int j = 0;
  double x = 0;
  double y = 0;
  while (j <= max_iter) {
    x = 0.5 * (x_lo + x_hi);
    y = this->func(adapt, x);

    if (y == 0 || fabs(x_hi - x_lo) / 2.0 < epserr) {
      break;
    }

    if (signbit(y) == signbit(this->func(adapt, x_lo))) {
      x_lo = x;
    } else {
      x_hi = x;
    };

    // next iteration
    j += 1;
  };

  return x;
};
