#ifndef LIF_H
#define LIF_H

#include <string>

#include "IF.h"

// Leaky integrate and fire model
class LIF : public IF
{
public:

  // constructors
  LIF(double mu, double D): IF(mu, D) {type="LIF";};
  LIF(std::string input_file): IF(input_file) {type="LIF";};

  // drift
  double drift(double v, double t) const;
};

#endif //LIF_H
