#ifndef TWOCOSINESIGNAL_H
#define TWOCOSINESIGNAL_H

#include "Signal.h"
#include <string>

class TwoCosineSignal : public Signal {
private:
  double alpha; // amplitude first signal
  double f1;    // frequency first signal
  double beta;  // amplitude second signal
  double f2;    // frequency second signal
  double phi;   // phase shift

public:
  // constructors
  TwoCosineSignal(double alpha, double f1, double beta, double f2, double phi);
  TwoCosineSignal(std::string input_file);

  // return signal
  double signal(double t) const;
};

#endif // TWOCOSINESIGNAL_H
