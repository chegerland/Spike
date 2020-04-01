#ifndef SIMULATION_H
#define SIMULATION_H

#include "../Options/Options.h"
#include "../TimeFrame/TimeFrame.h"

class Simulation {
protected:
  Options opts;
  TimeFrame time_frame;

public:

  explicit Simulation(const Options& opts);

  virtual void run() = 0;
};

#endif // SIMULATION_H
