/**
 * @file IFAC.h
 * @author C. H. Egerland
 */

#ifndef IFAC_H
#define IFAC_H

#include <cassert>
#include <cmath>
#include <vector>

#include "../../Signal/CosineSignal.h"
#include "../../Signal/Signal.h"
#include "../../SpikeTrain/SpikeTrain.h"
#include "../../TimeFrame/TimeFrame.h"
#include "../Neuron.h"

#include <random>

/**
 * @class IFAC
 * @brief An abstract base class for integrate-and-fire neurons with an
 * adaptation current.
 * Similar to the IF class, but with an adaptation current
 */
class IFAC : public Neuron {
protected:
  double mu;                             ///< mean input current
  double D;                              ///< diffusion coefficient
  double tau_a;                          ///< adaptation time constant
  double Delta;                          ///< kick size of the adaptation
  std::random_device rd;                 ///< random device (seeding)
  std::mt19937 generator;                ///< random number generator
  std::normal_distribution<double> dist; ///< normal distribution

public:
  /**
   * @brief Construct IFAC from input file.
   * @param input_file Input file in .json format.
   */
  explicit IFAC(const std::string &input_file);

  /**
   * @brief Construct IFAC from parameters
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  IFAC(double mu, double D, double tau_a, double Delta);

  /**
   * @brief Returns the drift of the IFAC neuron.
   * @param v Voltage
   * @param t Time
   * @return Drift
   */
  virtual double drift(double v) const = 0;

  /**
   * @brief Returns the diffusion of the IFAC neuron.
   * The diffusion is given by sqrt(2*D).
   * @return Diffusion of IFAC neuron.
   */
  double diffusion() const;

  /**
   * @brief Fills the spike train.
   * Returns a spike train, i.e. an array with as many steps as the time frame,
   * that (at the appropriate entry) is false if the neuron has not spiked and
   * true if it has spiked in the corresponding time bin. We use the
   * Euler-Maruyama-Scheme to solve the SDE for the IF neuron an simply put a
   * true into the spike train array, whenever the neuron spikes.
   * @param time Time frame
   * @param spike_train Spike train
   */
  void get_spike_train(const TimeFrame &time, SpikeTrain &spike_train) override;

  /**
   * @brief Fills the spike train.
   * Returns a spike train, i.e. an array with as many steps as the time frame,
   * that (at the appropriate entry) is false if the neuron has not spiked and
   * true if it has spiked in the corresponding time bin. We use the
   * Euler-Maruyama-Scheme to solve the SDE for the IF neuron an simply put a
   * true into the spike train array, whenever the neuron spikes.
   * @param time Time frame
   * @param signal Signal
   * @param spike_train Spike train
   */
  void get_spike_train(const TimeFrame &time, const Signal &signal,
                       SpikeTrain &spike_train) override;

  /**
   * @brief Returns a trajectory, i.e. v(t).
   * @param [in] time TimeFrame
   * @param [out] v Array of voltages at times given by time frame
   * @param [out] a Array of adaptation values at times given by time frame
   */
  void get_voltage_curve(const TimeFrame &time, double *v, double *a);

  /**
   * @brief Setter method for mean input current.
   * @param mu_new Mean input current
   */
  void set_mu(double mu_new) { this->mu = mu_new; };

  /**
   * @brief Setter method for diffusion coefficient.
   * @param D_new Diffusion coefficient
   */
  void set_D(double D_new) { this->D = D_new; };

  /**
   * @brief Print neuron parameters.
   * @param file File stream
   */
  void print_info(std::ofstream &file) override;
};

#endif // IFAC_H
