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

  // count spikes that occured in timeframe
  int count(Timeframe &time) const;
  int count(Timeframe &time, Signal &signal) const;
  int count(Timeframe &time, Adaptation &adapt) const;
  int count(Timeframe &time, Signal &signal, Adaptation &adapt) const;

  // spike times
  void spike_times(std::vector<double> &times, Timeframe &time) const;
  void spike_times(std::vector<double> &times, Timeframe &time,
                   Adaptation &adapt) const;

  // calculate firing rate
  void firing_rate(std::vector<double> &rate, Timeframe &time) const;
  void firing_rate(std::vector<double> &rate, Timeframe &time,
                   Signal &signal) const;
  void firing_rate(std::vector<double> &rate, Timeframe &time,
                   Adaptation &adapt) const;
  void firing_rate(std::vector<double> &rate, Timeframe &time, Signal &signal,
                   Adaptation &adapt) const;

  // get voltage curve, i.e. v(t) or v(t) and a(t)
  void voltage_curve(std::vector<double> &v, Timeframe &time) const;
  void voltage_curve(std::vector<double> &v, std::vector<double> &a,
                     Timeframe &time, Adaptation &adapt) const;

  // setter methods
  void set_mu(double mu) { this->mu = mu; };
  void set_D(double D) { this->D = D; };
};

#endif // IF_H
