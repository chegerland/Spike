#ifndef STEPSIGNAL_H
#define STEPSIGNAL_H

#include <string>

#include "Signal.h"

class StepSignal : public Signal {
private:
  double alpha;
  double t_0;

public:
  // constructors
  StepSignal(double alpha, double t_0);
  StepSignal(std::string input_file);

  // return signal
  double signal(double t) const;
};

#endif // STEPSIGNAL_H
