#include <fstream>
#include <iostream>
#include <random>
#include <vector>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "IF.h"

IF::IF(double mu, double D) : mu(mu), D(D) {
  assert(mu >= 0);
  assert(D >= 0);
}

IF::IF(const std::string& input_file) {
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read parameters
  this->mu = root.get<double>("Neuron.mu");
  assert(mu >= 0);
  this->D = root.get<double>("Neuron.D");
  assert(D >= 0);
}

// diffusion
double IF::diffusion(double v, double t) const { return sqrt(2 * D); }

// get the spike train of an IF neuron
std::vector<bool> IF::get_spike_train(const Timeframe &time) const {
  // initial values
  double v = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // array for spike train
  std::vector<bool> spike_train;
  spike_train.resize(time.get_steps());

  // euler maruyama scheme
  for (unsigned int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train[i] = true;
    }
  }

  return spike_train;
}

// get the spike train of an IF neuron
std::vector<bool> IF::get_spike_train(const Timeframe &time,
                                      const Signal &signal) const {
  // initial values
  double v = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // array for spike train
  std::vector<bool> spike_train;
  spike_train.resize(time.get_steps());

  // euler maruyama scheme
  for (unsigned int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + signal.signal(t) * dt +
         this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train[i] = true;
    }
  }

  return spike_train;
}

// get the spike train of an IF neuron
std::vector<bool> IF::get_spike_train(const Timeframe &time,
                                      const Adaptation &adapt) const {
  // initial values
  double v = 0;
  double a = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // array for spike train
  std::vector<bool> spike_train;
  spike_train.resize(time.get_steps());

  // euler maruyama scheme
  for (unsigned int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + this->diffusion(v, t) * dist(generator);
    a += adapt.adapt(a, t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a = adapt.reset_rule(a);
      spike_train[i] = true;
    }
  }

  return spike_train;
}

// get the spike train of an IF neuron
std::vector<bool> IF::get_spike_train(const Timeframe &time,
                                      const Signal &signal,
                                      const Adaptation &adapt) const {
  // initial values
  double v = 0;
  double a = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // array for spike train
  std::vector<bool> spike_train;
  spike_train.resize(time.get_steps());

  // euler maruyama scheme
  for (unsigned int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + signal.signal(t) * dt +
         this->diffusion(v, t) * dist(generator);
    a += adapt.adapt(a, t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a = adapt.reset_rule(a);
      spike_train[i] = true;
    }
  }

  return spike_train;
}

// voltage curve for IF
void IF::get_voltage_curve(std::vector<double> &v,
                           const Timeframe &time) const {
  // initial values
  v[0] = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (unsigned int i = 1; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v[i] = v[i - 1] + this->drift(v[i - 1], t) * dt +
           this->diffusion(v[i - 1], t) * dist(generator);

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
    }
  }
}

// voltage curve for IF with adaptation
void IF::get_voltage_curve(std::vector<double> &v, std::vector<double> &a,
                           const Timeframe &time,
                           const Adaptation &adapt) const {
  // initial values
  v[0] = 0;
  a[0] = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (unsigned int i = 1; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v[i] = v[i - 1] + this->drift(v[i - 1], t) * dt +
           this->diffusion(v[i - 1], t) * dist(generator);
    a[i] = a[i - 1] + adapt.adapt(a[i - 1], t) * dt;

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
      a[i] = adapt.reset_rule(a[i]);
    }
  }
}
