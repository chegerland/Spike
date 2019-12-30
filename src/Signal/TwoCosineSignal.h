#ifndef TWOCOSINESIGNAL_H
#define TWOCOSINESIGNAL_H

#include <string>

#include "Signal.h"

class TwoCosineSignal : public Signal
{
private:

  double alpha; // amplitude first signal
  double beta;  // amplitude second signal
  double phi;   // phase shift
  double f1;    // frequency first signal
  double f2;    // frequency second signal

public:

  // constructors
  TwoCosineSignal(double alpha, double beta, double phi, double f1, double f2): alpha(alpha), beta(beta), phi(phi), f1(f1), f2(f2) {};
  TwoCosineSignal(std::string input_file);

  // return signal
  double signal(double t);

  // print function
  void print_parameters();

};

#endif //TWOCOSINESIGNAL_H
