#include <iostream>
#include <vector>

// ini parser
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "IF.h"

IF::IF(double mu, double D) : mu(mu), D(D), generator(rd()), dist(0.0, 1.0) {
  assert(mu >= 0);
  assert(D >= 0);
}

IF::IF(const std::string &input_file) : generator(rd()), dist(0.0, 1.0) {
  // read ini
  pt::ptree root;
  pt::read_ini(input_file, root);

  // read parameters
  this->mu = root.get<double>("Neuron.mu");
  assert(mu >= 0);
  this->D = root.get<double>("Neuron.D");
  assert(D >= 0);
}

double IF::diffusion() const { return sqrt(2 * D); }

void IF::get_spikes(SpikeTrain &spike_train) {
  // initial value for voltage
  double v = 0;

  const double dt = spike_train.get_dt();
  const size_t length = spike_train.get_values().size();

  // perform euler maruyama scheme
  for (size_t i = 0; i < length; i++) {
    v += this->drift(v) * dt + this->diffusion() * dist(generator) * sqrt(dt);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train.add_spike(i);
    }
  }
}

void IF::get_spikes(Signal &signal, SpikeTrain &spike_train) {
  // initial value for voltage
  double v = 0;

  const double dt = spike_train.get_dt();
  const size_t length = spike_train.get_values().size();

  // perform euler maruyama scheme
  for (size_t i = 0; i < length; i++) {
    v += (this->drift(v) + signal.get_value(i)) * dt +
         this->diffusion() * dist(generator) * sqrt(dt);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train.add_spike(i);
    }
  }
}

void IF::get_voltage_curve(const TimeFrame &time, std::vector<double> &v) {
  // initial value for voltage
  v[0] = 0;

  const double dt = time.get_dt();

  // perform euler maruyama scheme
  for (size_t i = 1; i < time.get_size(); i++) {
    v[i] = v[i - 1] + this->drift(v[i - 1]) * dt +
           this->diffusion() * dist(generator) * sqrt(dt);

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
    }
  }
}

std::ostream& operator<< (std::ostream &out, const IF &neuron) {
  neuron.print(out);
  return out;
}

PIF::PIF(double mu, double D) : IF(mu, D) {}

PIF::PIF(const std::string &input_file) : IF(input_file) {
  // read ini
  pt::ptree root;
  pt::read_ini(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Neuron.type");
  assert(type == "PIF");
}

double PIF::drift(double v) const { return this->mu; }

LIF::LIF(double mu, double D) : IF(mu, D) {}

LIF::LIF(const std::string &input_file) : IF(input_file) {
  // read ini
  pt::ptree root;
  pt::read_ini(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Neuron.type");
  assert(type == "LIF");
}

inline double LIF::drift(double v) const { return (this->mu - v); }
