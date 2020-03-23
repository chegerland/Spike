#ifndef FIRINGRATEBOX_H
#define FIRINGRATEBOX_H

#include "FiringRate.h"

class FiringRateBox : public FiringRate {
public:
  void calculate() override;
};

#endif // FIRINGRATEBOX_H
