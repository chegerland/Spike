#ifndef FIRINGRATEFACTORY_H
#define FIRINGRATEFACTORY_H

#include "FiringRate.h"

class FiringRateFactory {
public:
  static FiringRate *create(const std::string &input_file,
                            const TimeFrame &time_frame);
};

#endif // FIRINGRATEFACTORY_H
