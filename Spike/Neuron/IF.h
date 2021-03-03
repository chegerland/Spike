/**
 * @file IF.h
 * @author C. H. Egerland
 */

#ifndef SPIKE_IF_H
#define SPIKE_IF_H

#include <cassert>
#include <cmath>
#include <ostream>
#include <random>
#include <vector>

#include "Spike/Neuron/Neuron.h"
#include "Spike/Signal/CosineSignal.h"
#include "Spike/Signal/Signal.h"
#include "Spike/SpikeTrain/SpikeTrain.h"
#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

/**
 * @brief Abstract base class for integrate-and-fire (IF) neurons
 */
class IF : public Neuron {
protected:
  double mu;                             ///< mean input current
  double D;                              ///< diffusion coefficient
  std::random_device rd;                 ///< random device (seeding)
  std::mt19937 generator;                ///< random number generator
  std::normal_distribution<double> dist; ///< normal distribution

public:
  /**
   * @brief Constructs an IF neuron from a .ini file.
   * @param input_file Path to .ini file
   */
  explicit IF(const std::string &input_file);

  /**
   * @brief Construct an IF neuron from given parameters.
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  IF(double mu, double D);

  /**
   * @brief Calculates the drift of the IF neuron.
   * @param v Voltage
   * @return Drift
   */
  [[nodiscard]] virtual double drift(double v) const = 0;

  /**
   * @brief Calculates the diffusion of the IF neurons, i.e. sqrt(2D).
   * @return Diffusion
   */
  [[nodiscard]] double diffusion() const;

  /**
   * @brief Obtains spikes by integrating the Langevin equation using an
   * Euler-Maruyama scheme.
   * @param spike_train Spike train
   */
  void get_spikes(SpikeTrain &spike_train) override;

  /**
   * @brief Obtains spikes by integrating the Langevin equation using an
   * Euler-Maruyama scheme. Neuron is subject to an applied signal
   * @param signal Signal
   * @param spike_train Spike train
   */
  void get_spikes(Signal &signal, SpikeTrain &spike_train) override;

  /**
   * @brief Calculates the trajectory, i.e. v(t) for a given time frame.
   * @param time Time frame
   * @param v Voltage array
   */
  void get_voltage_curve(const TimeFrame &time, std::vector<double> &v);

  /**
   * @brief Set new mean input current
   * @param mu_new new mean input current
   */
  void set_mu(double mu_new) { this->mu = mu_new; };

  /**
   * @brief Set new diffusion coefficient.
   * @param D_new diffusion coefficient
   */
  void set_D(double D_new) { this->D = D_new; };

  /**
   * @brief Returns the diffusion coefficient
   * @return diffusion coefficient
   */
  [[nodiscard]] double get_D() const { return D; };

  /**
   * @brief Prints the IF neuron to the outstream
   * @param out out stream
   */
  virtual void print(std::ostream &out) const = 0;

  /**
   * @brief Overloads the << operator, so we can print the neuron.
   * @param out out stream
   * @param neuron IF neuron
   * @return out stream
   */
  friend std::ostream &operator<<(std::ostream &out, const IF &neuron);
};

/**
 * @class PIF
 * @brief Implements a perfect integrate-and-fire (PIF) neuron.
 */
class PIF : public IF {
public:
  /**
   * @brief Construct PIF from parameters.
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  PIF(double mu, double D);

  /**
   * @brief Construct PIF from input file.
   * @param input_file Path to .ini file
   */
  explicit PIF(const std::string &input_file);

  /**
   * @brief Returns drift of the PIF neuron, i.e. mu
   * @param v Voltage
   * @return Drift of PIF
   */
  [[nodiscard]] double drift(double v) const override;

  /**
   * @brief Prints the PIF neuron to out stream.
   * @param out out stream
   */
  void print(std::ostream &out) const override {
    out << "PIF(mu: " << mu << ", D: " << D << ")";
  }
};

/**
 * @brief A leaky integrate-and-fire (LIF) neuron
 */
class LIF : public IF {
public:
  /**
   * @brief Constructs an LIF from given parameters.
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  LIF(double mu, double D);

  /**
   * @brief Constructs an LIF from .ini file
   * @param input_file Path to .ini file
   */
  explicit LIF(const std::string &input_file);

  /**
   * @brief Calculates drift of the LIF, i.e. mu - v
   * @param v Voltage
   * @return Drift of LIF
   */
  [[nodiscard]] double drift(double v) const override;

  /**
   * @brief Prints the LIF neuron to out stream.
   * @param out out stream
   */
  void print(std::ostream &out) const override {
    out << "LIF(mu: " << mu << ", D: " << D << ")";
  }
};

} // namespace Spike

#endif // SPIKE_IF_H