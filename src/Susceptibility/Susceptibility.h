/*
 * @file Susceptibility.h
 * @author C. H. Egerland
 */
#ifndef SUSCEPTIBILITY_H
#define SUSCEPTIBILITY_H

#include "../Signal/WhiteNoiseSignal.h"
#include "../SpikeTrain/SpikeTrain.h"
#include <memory>
#include <complex>

class Susceptibility {
protected:
  std::shared_ptr<WhiteNoiseSignal> signal;
  std::vector<std::complex<double>> suscept_values;
  size_t count;

public:
  explicit Susceptibility(const std::shared_ptr<WhiteNoiseSignal> &signal);

  virtual void
  add_spike_train(const std::shared_ptr<SpikeTrain> &spike_train) = 0;

  void add_susceptibility(const std::vector<std::complex<double>> &suscept);

  const std::vector<std::complex<double>> &get_values() const {
    return suscept_values;
  };
};

#endif // SUSCEPTIBILITY_H
