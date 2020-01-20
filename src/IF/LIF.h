#ifndef LIF_H
#define LIF_H

#include <string>

#include "IF.h"

// Leaky integrate and fire model
class LIF : public IF {
public:
  // constructors
  LIF(double mu, double D);
  LIF(std::string input_file);

  // drift
  double drift(double v, double t) const;
};

#endif // LIF_H
