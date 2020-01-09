#ifndef IF_H
#define IF_H

#include <math.h>
#include <vector>
#include <cassert>

#include "../Signal/Signal.h"
#include "../Signal/CosineSignal.h"
#include "../Adaptation/Adaptation.h"
#include "../Timeframe/Timeframe.h"

// A generic integrate and fire model.
class IF
{
protected:

  double mu;        // mobility
  double D;         // diffusion coefficient
  std::string type; // type of the IF

public:

  // constructors
  IF(std::string input_file);
  IF(double mu, double D): mu(mu), D(D)
  {
    assert(mu >= 0);
    assert(D >= 0);
  };

  // drift and diffusion of IF neuron
  virtual double drift(double v, double t) const =0;
  double diffusion(double v, double t) const;

  // count spikes that occured in timeframe
  int count(Timeframe &time) const;
  int count(Timeframe &time, Signal &signal) const;
  int count(Timeframe &time, Adaptation &adapt) const;
  int count(Timeframe &time, Signal &signal, Adaptation &adapt) const;

  // calculate firing rate
  void firing_rate(std::vector<double> &rate, Timeframe &time) const;
  void firing_rate(std::vector<double> &rate, Timeframe &time, Signal &signal) const;
  void firing_rate(std::vector<double> &rate, Timeframe &time, Adaptation &adapt) const;
  void firing_rate(std::vector<double> &rate, Timeframe &time, Signal &signal, Adaptation &adapt) const;

  // get voltage curve, i.e. v(t) or v(t) and a(t)
  void voltage_curve(std::vector<double> &v, Timeframe &time) const;
  void voltage_curve(std::vector<double> &v, std::vector<double> &a, Timeframe &time, Adaptation &adapt) const;

  // setter methods
  void set_mu(double mu){this->mu = mu;};
  void set_D(double D){this->D = D;};

  // print the parameters of this neuron
  void print_parameters() const;
};

#endif // IF_H
