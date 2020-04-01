#ifndef FIRINGRATESIMULATION_H
#define FIRINGRATESIMULATION_H

#include "Simulation.h"
#include "../FiringRate/FiringRate.h"
#include "../Neuron/Neuron.h"

class FiringRateSimulation : public Simulation {
private:
  FiringRate *firing_rate;
  Neuron *neuron;
  Signal *signal;
  int N_neurons;
  bool signal_given = false;

public:

  explicit FiringRateSimulation(const Options& opts);

  ~FiringRateSimulation();

  void run();
};

#endif // FIRINGRATESIMULATION_H
