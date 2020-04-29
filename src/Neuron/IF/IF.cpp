#include <iostream>
#include <vector>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "IF.h"

IF::IF(double mu, double D) : mu(mu), D(D), generator(rd()), dist(0.0, 1.0) {
  assert(mu >= 0);
  assert(D >= 0);
}

IF::IF(const std::string &input_file) : generator(rd()), dist(0.0, 1.0) {
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

void IF::get_spike_train(const std::shared_ptr<SpikeTrain> &spike_train) {
  // initial value for voltage
  double v = 0;

  const double dt = spike_train->get_time_frame()->get_dt();
  const size_t length = spike_train->get_time_frame()->get_steps();

  // perform euler maruyama scheme
  for (size_t i = 0; i < length; i++) {
    v += this->drift(v) * dt + this->diffusion() * dist(generator) * sqrt(dt);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train->add_spike(i);
    }
  }
}

void IF::get_spike_train(const std::shared_ptr<Signal> &signal,
                         const std::shared_ptr<SpikeTrain> &spike_train) {
  // initial value for voltage
  double v = 0;

  const double dt = spike_train->get_time_frame()->get_dt();
  const size_t length = spike_train->get_time_frame()->get_steps();

  // perform euler maruyama scheme
  for (size_t i = 0; i < length; i++) {
    v += (this->drift(v) + signal->get_value(i)) * dt +
         this->diffusion() * dist(generator) * sqrt(dt);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      spike_train->add_spike(i);
    }
  }
}

void IF::get_voltage_curve(const TimeFrame &time, double *v) {
  // initial value for voltage
  v[0] = 0;

  double dt = time.get_dt();

  // perform euler maruyama scheme
  for (size_t i = 1; i < time.get_steps(); i++) {
    v[i] = v[i - 1] + this->drift(v[i - 1]) * dt +
           this->diffusion() * dist(generator) * sqrt(dt);

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
    }
  }
}

void IF::print_info(std::ofstream &file) const {
  // print neuron parameters to file
  file << "# Neuron parameters: "
       << "\n"
       << "# mu = " << mu << "\n"
       << "# D = " << D << "\n";
}
