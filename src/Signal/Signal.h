#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

//! A generic signal
class Signal {
protected:
  std::string type; // type of signal

public:
  // constructors
  Signal();
  Signal(std::string input_file);

  // Returns the signal at time t
  virtual double signal(double t) = 0;

  // print signal parameters
  virtual void print_parameters() = 0;
};

#endif // SIGNAL_H
