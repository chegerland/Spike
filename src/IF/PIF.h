#ifndef PIF_H
#define PIF_H

#include "IF.h"

// Perfect integrate and fire model
class PIF : public IF
{
public:

  // constructors
  PIF(double mu, double D): IF(mu, D) {type="PIF";};
  PIF(std::string input_file): IF(input_file) {type="PIF";};

  // drift
  double drift(double v, double t) const;
};

#endif // PIF_H
