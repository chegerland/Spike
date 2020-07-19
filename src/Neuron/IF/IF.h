#ifndef IF_H
#define IF_H

#include <cassert>
#include <cmath>
#include <vector>

#include "../../Signal/CosineSignal.h"
#include "../../Signal/Signal.h"
#include "../../SpikeTrain/SpikeTrain.h"
#include "../../TimeFrame/TimeFrame.h"
#include "../Neuron.h"
#include <random>

class IF : public Neuron {
protected:
  double mu;                             ///< mean input current
  double D;                              ///< diffusion coefficient
  std::random_device rd;                 ///< random device (seeding)
  std::mt19937 generator;                ///< random number generator
  std::normal_distribution<double> dist; ///< normal distribution

public:
  explicit IF(const std::string &input_file);
  IF(double mu, double D);

  [[nodiscard]] virtual double drift(double v) const = 0;
  [[nodiscard]] double diffusion() const;

  void get_spikes(SpikeTrain &spike_train) override;
  void get_spikes(Signal &signal, SpikeTrain &spike_train) override;

  void get_voltage_curve(const TimeFrame &time, std::vector<double> &v);

  void set_mu(double mu_new) { this->mu = mu_new; };
  void set_D(double D_new) { this->D = D_new; };

  void print_info(std::ofstream &file) const override;
};

#endif // IF_H
