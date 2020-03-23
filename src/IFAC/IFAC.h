#ifndef IFAC_H
#define IFAC_H

#include <cassert>
#include <cmath>
#include <vector>

#include "../Signal/CosineSignal.h"
#include "../Signal/Signal.h"
#include "../SpikeTrain/SpikeTrain.h"
#include "../TimeFrame/TimeFrame.h"

/**
 * @class IFAC
 * @brief An abstract base class for integrate-and-fire neurons with an
 * adaptation current.
 */
class IFAC {
protected:
  double mu;    ///< mean input current
  double D;     ///< diffusion coefficient
  double tau_a; ///< adaptation time constant
  double Delta; ///< kick size of the adaptation

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
   * @brief Returns the diffusion of the IFAC neuron, i.e. in general sqrt(2 * D)
   * @return Diffusion of IFAC neuron, i.e. sqrt(2*D)
   */
  double diffusion() const;

  /**
   * Returns a spike train, i.e. an array with as many steps as the time frame,
   * that contains a zero if the neuron has not spiked and a 1 if it has spiked
   * in the corresponding time bin.
   * We use the Euler-Maruyama-Scheme to solve the SDE for the IFAC neuron an
   * simply put a 1 into the spike train array, whenever the neuron spikes.
   * @brief Returns a spike train.
   * @param time TimeFrame
   */
  void get_spike_train(const TimeFrame &time, SpikeTrain &spike_train) const;

  /**
   * Produces a spike train, i.e. an array with as many steps as the time frame,
   * that contains a zero if the neuron has not spiked and a 1 if it has spiked
   * in the corresponding time bin.
   * We use the Euler-Maruyama-Scheme to solve the SDE for the IFAC neuron an
   * simply put a 1 into the spike train array, whenever the neuron spikes.
   * @brief Returns a spike train, where IFAC is subject to a get_value.
   * @param time TimeFrame
   * @param signal Signal
   * @return A spike train
   */
  void get_spike_train(const TimeFrame &time, const Signal &signal,
                       SpikeTrain &spike_train) const;

  /**
   * @brief Returns a trajectory, i.e. v(t).
   * @param [out] v Array of voltages at times given by time frame
   * @param time TimeFrame
   */
  void get_voltage_curve(const TimeFrame &time, double *v, double *a) const;

  /**
   * @brief Setter method for mean input current.
   * @param mu_new Mean input current
   */
  void set_mu(double mu_new) { this->mu = mu_new; };

  /**
   * @brief Setter method for diffusion coefficient.
   * @param D_new
   */
  void set_D(double D_new) { this->D = D_new; };
};

#endif // IFAC_H
