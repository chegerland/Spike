#include <iostream>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "IFAC.h"

// constructor from parameters
IFAC::IFAC(double mu, double D, double tau_a, double Delta)
    : mu(mu), D(D), tau_a(tau_a), Delta(Delta), generator(rd()),
      dist(0.0, 1.0) {
  assert(mu >= 0);
  assert(D >= 0);
  assert(tau_a > 0);
  assert(Delta >= 0);
}

// constructor from input file
IFAC::IFAC(const std::string &input_file) : generator(rd()), dist(0.0, 1.0) {
  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // read parameters
  this->mu = root.get<double>("Neuron.mu");
  assert(mu >= 0);
  this->D = root.get<double>("Neuron.D");
  assert(D >= 0);
  this->tau_a = root.get<double>("Neuron.tau_a");
  assert(tau_a > 0);
  this->Delta = root.get<double>("Neuron.Delta");
  assert(Delta >= 0);
}

// diffusion
double IFAC::diffusion() const { return sqrt(2 * D); }

// get the spike train of an IFAC neuron
void IFAC::get_spike_train(const TimeFrame &time,
                           SpikeTrain &spike_train) {
  // initial values
  double v = 0;
  double a = 0;

  // for better readibility
  double dt = time.get_dt();

  // perform euler maruyama scheme
  for (size_t i = 0; i < time.get_steps(); i++) {
    v += (this->drift(v) - a) * dt +
         this->diffusion() * dist(generator) * sqrt(dt);
    a += -1. / tau_a * a * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += Delta;
      spike_train.set_spike(i);
    }
  }
}

// get the spike train of an IFAC neuron with signal
void IFAC::get_spike_train(const TimeFrame &time, const Signal &signal,
                           SpikeTrain &spike_train) {
  // initial values
  double v = 0;
  double a = 0;

  // for better readibility
  double dt = time.get_dt();

  // perform euler maruyama scheme
  for (size_t i = 0; i < time.get_steps(); i++) {
    v += (this->drift(v) - a + signal.get_value(i)) * dt +
         this->diffusion() * dist(generator) * sqrt(dt);
    a += -1. / tau_a * a * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += Delta;
      spike_train.set_spike(i);
    }
  }
}

// get voltage curve, i.e. v(t) and a(t)
void IFAC::get_voltage_curve(const TimeFrame &time, double *v,
                             double *a) {
  // initial values
  v[0] = 0;
  a[0] = 0;

  // for better readibility
  double dt = time.get_dt();

  // perform euler maruyama scheme
  for (size_t i = 1; i < time.get_steps(); i++) {
    v[i] = v[i - 1] + (this->drift(v[i - 1]) - a[i - 1]) * dt +
           this->diffusion() * dist(generator) * sqrt(dt);
    a[i] = a[i - 1] - 1. / tau_a * a[i - 1] * dt;

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
      a[i] += Delta;
    }
  }
}

// print neuron parameters
void IFAC::print_info(std::ofstream &file) {
  file << "# Neuron parameters: "
       << "\n"
       << "# mu = " << mu << "\n"
       << "# D = " << D << "\n"
       << "# tau_a = " << tau_a << "\n"
       << "# Delta = " << Delta << "\n";
}
