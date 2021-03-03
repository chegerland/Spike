#include <iostream>

// ini parser
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "Spike/Neuron/IFAC.h"

namespace Spike {

// constructor from parameters
IFAC::IFAC(double mu, double D, double tau_a, double Delta)
    : IF(mu, D), tau_a(tau_a), Delta(Delta) {
  assert(mu >= 0);
  assert(D >= 0);
  assert(tau_a > 0);
  assert(Delta >= 0);
}

// constructor from input file
IFAC::IFAC(const std::string &input_file) : IF(input_file) {
  // read ini
  pt::ptree root;
  pt::read_ini(input_file, root);

  this->tau_a = root.get<double>("Neuron.tau_a");
  assert(tau_a > 0);
  this->Delta = root.get<double>("Neuron.Delta");
  assert(Delta >= 0);
}

// get the spike train of an IFAC neuron
void IFAC::get_spikes(SpikeTrain &spike_train) {
  // initial values
  double v = 0;
  double a = 0;

  const double dt = spike_train.get_dt();
  const size_t length = spike_train.get_size();
  const double diff_factor = this->diffusion() * sqrt(dt);

  // perform euler maruyama scheme
  for (size_t i = 0; i < length; i++) {
    v += (this->drift(v) - a) * dt + diff_factor * dist(generator);
    a += -1. / tau_a * a * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += Delta;
      spike_train.add_spike(i);
    }
  }
}

// get the spike train of an IFAC neuron with signal
void IFAC::get_spikes(Signal &signal, SpikeTrain &spike_train) {
  // initial values
  double v = 0;
  double a = 0;

  const double dt = spike_train.get_dt();
  const size_t length = spike_train.get_size();
  const double diff_factor = this->diffusion() * sqrt(dt);

  // perform euler maruyama scheme
  for (size_t i = 0; i < length; i++) {
    v += (this->drift(v) - a + signal.get_value(i)) * dt +
         diff_factor * dist(generator);
    a += -1. / tau_a * a * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a += Delta;
      spike_train.add_spike(i);
    }
  }
}

// get voltage curve, i.e. v(t) and a(t)
void IFAC::get_voltage_curve(const TimeFrame &time, std::vector<double> &v,
                             std::vector<double> &a) {
  // initial values
  v[0] = 0;
  a[0] = 0;

  // for better readibility
  const double dt = time.get_dt();
  const double diff_factor = this->diffusion() * sqrt(dt);

  // perform euler maruyama scheme
  for (size_t i = 1; i < time.get_size(); i++) {
    v[i] = v[i - 1] + (this->drift(v[i - 1]) - a[i - 1]) * dt +
           diff_factor * dist(generator);
    a[i] = a[i - 1] - 1. / tau_a * a[i - 1] * dt;

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
      a[i] += Delta;
    }
  }
}

// constructor from parameters
PIFAC::PIFAC(double mu, double D, double tau_a, double Delta)
    : IFAC(mu, D, tau_a, Delta) {}

// constructor from input file
PIFAC::PIFAC(const std::string &input_file) : IFAC(input_file) {
  // read ini
  pt::ptree root;
  pt::read_ini(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Neuron.type");
  assert(type == "PIFAC");
}

// drift of a PIFAC neuron
double PIFAC::drift(double v) const { return this->mu; }

// constructor from parameters
LIFAC::LIFAC(double mu, double D, double tau_a, double Delta)
    : IFAC(mu, D, tau_a, Delta) {}

// constructor from input file
LIFAC::LIFAC(const std::string &input_file) : IFAC(input_file) {
  // read ini
  pt::ptree root;
  pt::read_ini(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Neuron.type");
  assert(type == "LIFAC");
}

// drift of an LIFAC neuron
double LIFAC::drift(double v) const { return (this->mu - v); }

} // namespace Spike