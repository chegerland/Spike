#ifndef IF_H
#define IF_H

#include <cassert>
#include <math.h>
#include <vector>

#include "../Adaptation/Adaptation.h"
#include "../Signal/CosineSignal.h"
#include "../Signal/Signal.h"
#include "../Timeframe/Timeframe.h"

// A generic integrate and fire model.
class IF {
protected:
  double mu; // mobility
  double D;  // diffusion coefficient

public:
  // constructors
  IF(std::string input_file);
  IF(double mu, double D);

  // drift and diffusion of IF neuron
  virtual double drift(double v, double t) const = 0;
  double diffusion(double v, double t) const;

  // get a spike train, i.e. array with 0s and 1s
  std::vector<bool> get_spike_train(const Timeframe &time) const;
  std::vector<bool> get_spike_train(const Timeframe &time,
                                    const Signal &signal) const;
  std::vector<bool> get_spike_train(const Timeframe &time,
                                    const Adaptation &adapt) const;
  std::vector<bool> get_spike_train(const Timeframe &time, const Signal &signal,
                                    const Adaptation &adapt) const;

  // get voltage curve, i.e. v(t) or v(t) and a(t)
  void get_voltage_curve(std::vector<double> &v, const Timeframe &time) const;
  void get_voltage_curve(std::vector<double> &v, std::vector<double> &a,
                         const Timeframe &time, const Adaptation &adapt) const;

  // setter methods
  void set_mu(double mu) { this->mu = mu; };
  void set_D(double D) { this->D = D; };
};

#endif // IF_H
