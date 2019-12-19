#ifndef IF_H
#define IF_H

#include <math.h>
#include <vector>

#include "../Signal/Signal.h"
#include "../Adaptation/Adaptation.h"
#include "../Timeframe/Timeframe.h"

// A generic integrate and fire model.
class IF
{
protected:

  // mobility
  double mu;

  // diffusion coefficient
  double D;

  // type of the IF
  std::string type;

public:

  // constructor
  IF(double mu, double D): mu(mu), D(D) {};
  IF(std::string input_file);

  // drift and diffusion of IF neuron
  virtual double drift(double v, double t) const =0;
  double diffusion(double v, double t) const;

  // simply count spike that occured in timeframe
  int count(Timeframe *time) const;
  int count(Timeframe *time, Signal *signal) const;
  int count(Timeframe *time, Adaptation *adapt) const;
  int count(Timeframe *time, Signal *signal, Adaptation *adapt) const;

  // put firing rate into array
  void firing_rate(double* rate, Timeframe *time) const;
  void firing_rate(double* rate, Timeframe *time, Signal *signal) const;
  void firing_rate(double* rate, Timeframe *time, Adaptation *adapt) const;
  void firing_rate(double* rate, Timeframe *time, Signal *signal, Adaptation *adapt) const;

  // voltage curve, i.e. v(t) or v(t) and a(t)
  void voltage_curve(double *v, Timeframe *time) const;
  void voltage_curve(double *v, double *a, Timeframe *time, Adaptation *adapt) const;

  // print the parameters of this neuron
  void print_parameters() const;
};

#endif // IF_H
