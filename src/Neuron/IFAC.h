/**
 * @file IFAC.h
 * @author C. H. Egerland
 */
#ifndef IFAC_H
#define IFAC_H

#include <cassert>
#include <cmath>
#include <vector>

#include "../Signal/Signal.h"
#include "../SpikeTrain/SpikeTrain.h"
#include "../TimeFrame/TimeFrame.h"
#include "IF.h"

#include <random>

/**
 * @brief An abstract base class for integrate-and-fire neurons with an
 * adaptation current.
 */
class IFAC : public IF {
protected:
  double tau_a; ///< adaptation time constant
  double Delta; ///< kick size of the adaptation
public:
  /**
   * @brief Construct IFAC from .ini file.
   * @param input_file Path to .ini file.
   */
  explicit IFAC(const std::string &input_file);

  /**
   * @brief Construct IFAC from given parameters
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  IFAC(double mu, double D, double tau_a, double Delta);

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
   * @brief Calculates the trajectory, i.e. v(t) and a(t) for a given time
   * frame.
   * @param time Time frame
   * @param v Voltage array
   * @param a Adaptation variable array
   */
  void get_voltage_curve(const TimeFrame &time, std::vector<double> &v,
                         std::vector<double> &a);
};

/**
 * @brief Implement a perfect integrate-and-fire neuron with an adaptation
 * current (PIFAC).
 */
class PIFAC : public IFAC {
public:
  /**
   * @brief Construct PIFAC from parameters.
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  PIFAC(double mu, double D, double tau_a, double Delta);

  /**
   * @brief Construct PIFAC from .ini file.
   * @param input_file Path to .ini file.
   */
  explicit PIFAC(const std::string &input_file);

  /**
   * @brief Returns drift of the PIFAC neuron, i.e. mu
   * @param v Voltage
   * @param t time
   * @return Drift of PIFAC, i.e. mu
   */
  [[nodiscard]] double drift(double v) const override;

  void print(std::ostream &out) const override {
    out << "PIFAC(mu: " << mu << ", D: " << D << ", tau_a: " << tau_a
        << ", Delta: " << Delta << ")";
  }
};

/**
 * @brief Implements a leaky integrate-and-fire neuron with an adaptation
 * current (LIFAC).
 */
class LIFAC : public IFAC {
public:
  /**
   * @brief Construct LIFAC from parameters.
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  LIFAC(double mu, double D, double tau_a, double Delta);

  /**
   * @brief Construct LIFAC from .ini file.
   * @param input_file Path to .ini file
   */
  explicit LIFAC(const std::string &input_file);

  /**
   * @brief Returns the drift of the LIFAC neuron, i.e. mu - v
   * @param v Voltage
   * @param t Time
   * @return Drift of LIFAC
   */
  [[nodiscard]] double drift(double v) const override;

  void get_kernel(const TimeFrame &time, const Signal &signal,
                  const double norm, double *kernel) const;

  void print(std::ostream &out) const override {
    out << "LIFAC(mu: " << mu << ", D: " << D << ", tau_a: " << tau_a
        << ", Delta: " << Delta << ")";
  }
};

#endif // IFAC_H
