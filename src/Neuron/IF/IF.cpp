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

IF::IF(const std::string &input_file) {
  // read json
  pt::ptree root;
  pt::read_json(input_file, root);

  // read parameters
  this->mu = root.get<double>("Neuron.mu");
  assert(mu >= 0);
  this->D = root.get<double>("Neuron.D");
  assert(D >= 0);
}

double IF::diffusion() const { return sqrt(2 * D); }

void IF::get_spike_train(const TimeFrame &time, SpikeTrain &spike_train) const {
  // initial value for voltage
  double v = 0;

  double dt = time.get_dt();

  // initialize rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // perform euler maruyama scheme
  for (unsigned int i = 0; i < time.get_steps(); i++) {
    v += this->drift(v) * dt + this->diffusion() * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train.set_spike(i);
    }
  }
}

void IF::get_spike_train(const TimeFrame &time, const Signal &signal,
                         SpikeTrain &spike_train) const {
  // initial value for voltage
  double v = 0;

  double dt = time.get_dt();

  // initialize rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // perform euler maruyama scheme
  for (unsigned int i = 0; i < time.get_steps(); i++) {
    v += (this->drift(v) + signal.get_value(i)) * dt +
         this->diffusion() * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train.set_spike(i);
    }
  }
}

void IF::get_voltage_curve(const TimeFrame &time, double *v) const {
  // initial value for voltage
  v[0] = 0;

  double dt = time.get_dt();

  // initialize rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // perform euler maruyama scheme
  for (unsigned int i = 1; i < time.get_steps(); i++) {
    v[i] = v[i - 1] + this->drift(v[i - 1]) * dt +
           this->diffusion() * dist(generator);

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
    }
  }
}

void IF::print_info(std::ofstream& file) {
  // print neuron parameters to file
  file << "# Neuron parameters: " << "\n"
       << "# mu = " << mu << "\n"
       << "# D = " << D << "\n";
}
