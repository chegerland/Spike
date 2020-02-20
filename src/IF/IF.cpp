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
};

IF::IF(std::string input_file) {
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read parameters
  this->mu = root.get<double>("Neuron.mu");
  assert(mu >= 0);
  this->D = root.get<double>("Neuron.D");
  assert(D >= 0);
};

// diffusion
double IF::diffusion(double v, double t) const { return sqrt(2 * D); };

// count spikes of an IF neuron
int IF::count(Timeframe &time) const {
  int count = 0;

  // initial values
  double v = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      count += 1;
    };
  };

  return count;
};

// count spikes of an IF neuron with signal
int IF::count(Timeframe &time, Signal &signal) const {
  int count = 0;

  // initial values
  double v = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal.signal(t) * dt +
         diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      count += 1;
    };
  };

  return count;
};

// count spikes of an IF neuron with adaptation
int IF::count(Timeframe &time, Adaptation &adapt) const {
  int count = 0;

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

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt - a * dt + diffusion(v, t) * dist(generator);
    a += adapt.adapt(a, t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a = adapt.reset_rule(a);
      count += 1;
    };
  };

  return count;
};

// count spikes of an IF neuron with signal and adaptation
int IF::count(Timeframe &time, Signal &signal, Adaptation &adapt) const {
  int count = 0;

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

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal.signal(t) * dt - a * dt +
         diffusion(v, t) * dist(generator);
    a += adapt.adapt(a, t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a = adapt.reset_rule(a);
      count += 1;
    };
  };

  return count;
};

// calculate firing rate of an IF neuron
void IF::spike_times(std::vector<double> &times, Timeframe &time) const {
  // initial values
  double v = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      times.push_back(t);
    };
  };
};

// calculate firing rate of an IF neuron
void IF::spike_times(std::vector<double> &times, Timeframe &time,
                     Adaptation &adapt) const {
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

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt - a * dt + diffusion(v, t) * dist(generator);
    a += adapt.adapt(a, t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a = adapt.reset_rule(a);
      times.push_back(t);
    };
  };
};

// calculate firing rate of an IF neuron
void IF::firing_rate(std::vector<double> &rate, Timeframe &time) const {
  // initial values
  double v = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += this->drift(v, t) * dt + this->diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      rate[i] += 1.0 / dt;
    };
  };
};

// calculate firing rate of an IF neuron with signal
void IF::firing_rate(std::vector<double> &rate, Timeframe &time,
                     Signal &signal) const {
  // initial values
  double v = 0;
  double t = time.get_t_0();

  // for better readibility
  double dt = time.get_dt();

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal.signal(t) * dt +
         diffusion(v, t) * dist(generator);

    // fire and reset rule
    if (v > 1) {
      v = 0;
      rate[i] += 1.0 / dt;
    };
  };
};

// calculate firing rate of an IF neuron with adaptation
void IF::firing_rate(std::vector<double> &rate, Timeframe &time,
                     Adaptation &adapt) const {
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

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt - a * dt + diffusion(v, t) * dist(generator);
    a += adapt.adapt(a, t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a = adapt.reset_rule(a);
      rate[i] += 1.0 / dt;
    };
  };
};

// calculate firing rate of an IF neuron with signal and adaptation
void IF::firing_rate(std::vector<double> &rate, Timeframe &time, Signal &signal,
                     Adaptation &adapt) const {
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

  // euler maruyama scheme
  for (int i = 0; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v += drift(v, t) * dt + signal.signal(t) * dt - a * dt +
         diffusion(v, t) * dist(generator);
    a += adapt.adapt(a, t) * dt;

    // fire and reset rule
    if (v > 1) {
      v = 0;
      a = adapt.reset_rule(a);
      rate[i] += 1.0 / dt;
    };
  };
};

// voltage curve for IF
void IF::voltage_curve(std::vector<double> &v, Timeframe &time) const {
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
  for (int i = 1; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v[i] = v[i - 1] + this->drift(v[i - 1], t) * dt +
           this->diffusion(v[i - 1], t) * dist(generator);

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
    };
  };
};

// voltage curve for IF with adaptation
void IF::voltage_curve(std::vector<double> &v, std::vector<double> &a,
                       Timeframe &time, Adaptation &adapt) const {
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
  for (int i = 1; i < time.get_steps(); i++) {
    // update time and voltage
    t += dt;
    v[i] = v[i - 1] + this->drift(v[i - 1], t) * dt +
           this->diffusion(v[i - 1], t) * dist(generator);
    a[i] = a[i - 1] + adapt.adapt(a[i - 1], t) * dt;

    // fire and reset rule
    if (v[i] > 1) {
      v[i] = 0;
      a[i] = adapt.reset_rule(a[i]);
    };
  };
};
