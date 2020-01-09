#ifndef COSINESIGNAL_H
#define COSINESIGNAL_H

#include <string>

#include "Signal.h"

class CosineSignal : public Signal
{
private:

  double alpha; // amplitube
  double f;     // frequency

public:

  // constructors
  CosineSignal(double alpha, double f): alpha(alpha), f(f) {};
  CosineSignal(std::string input_file);

  // return signal
  double signal(double t);

  // getter functions
  double get_f(){return this->f;};

  // print function
  void print_parameters();

};

#endif //COSINESIGNAL_H
