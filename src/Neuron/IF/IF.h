/**
 * @file IF.h
 * @author C. H. Egerland
 */

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

/**
 * @class IF
 * @brief An abstract base class for integrate-and-fire neurons.
 * All integrate-and-fire neurons shall have the same diffusion, but differ in
 * their drift function.
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
   * @brief Construct IF from input file.
   * @param input_file Input file in .json format.
   */
  explicit IF(const std::string &input_file);

  /**
   * @brief Construct IF from parameters.
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  IF(double mu, double D);

  /**
   * @brief Returns the drift of the IF neuron.
   * @param v Voltage
   * @return Drift of the neuron
   */
  virtual double drift(double v) const = 0;

  /**
   * @brief Returns the diffusion of the IF neuron.
   * The diffusion is given by sqrt(2*D).
   * @return Diffusion of the neuron.
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
  void get_spike_train(const std::shared_ptr<SpikeTrain> &spike_train) override;

  /**
   * @brief Fills the spike train.
   * Returns a spike train, i.e. an array with as many steps as the time frame,
   * that (at the appropriate entry) is false if the neuron has not spiked and
   * true if it has spiked in the corresponding time bin. We use the
   * Euler-Maruyama-Scheme to solve the SDE for the IF neuron an simply put a
   * true into the spike train array, whenever the neuron spikes.
   * @brief Returns a spike train, where IF is subject to a get_value.
   * @param time Time frame
   * @param signal Signal
   * @param spike_train Spike train
   */
  void get_spike_train(const std::shared_ptr<Signal> &signal,
                       const std::shared_ptr<SpikeTrain> &spike_train) override;

  /**
   * @brief Returns a trajectory, i.e. v(t).
   * @param [in] time TimeFrame
   * @param [out] v Array of voltages at times given by time frame
   */
  void get_voltage_curve(const TimeFrame &time, double *v);

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
  void print_info(std::ofstream &file) const override;
};

#endif // IF_H
