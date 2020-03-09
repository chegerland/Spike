#ifndef COSINESIGNAL_H
#define COSINESIGNAL_H

#include <string>

#include "Signal.h"

class CosineSignal : public Signal {
private:
  double alpha; // amplitube
  double f;     // frequency

public:
  // constructors
  CosineSignal(double alpha, double f);
  CosineSignal(std::string input_file);

  // return signal
  double signal(double t) const;

  // getter functions
  double get_f() const { return this->f; };
};

#endif // COSINESIGNAL_H
