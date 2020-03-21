#ifndef IF_H
#define IF_H

#include <cassert>
#include <cmath>
#include <vector>

#include "../Adaptation/Adaptation.h"
#include "../Signal/CosineSignal.h"
#include "../Signal/Signal.h"
#include "../Timeframe/Timeframe.h"

/**
 * @class IF
 * @brief An abstract base class for integrate-and-fire neurons.
 */
class IF {
protected:
  double mu; ///< mean input current
  double D;  ///< diffusion coefficient

public:
<<<<<<< HEAD
  // constructors
  IF(const std::string& input_file);
=======
  /**
   * @brief Construct IF from input file.
   * @param input_file Input file in .json format.
   */
  IF(const std::string& input_file);

  /**
   * @brief Construct IF from parameters
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
>>>>>>> 17fc4e88a39ac8c59e4d5c4f86a4cebd3b9e25a8
  IF(double mu, double D);

  /**
   * @brief Returns the drift of the IF neuron.
   * @param v Voltage
   * @param t Time
   * @return Drift
   */
  virtual double drift(double v, double t) const = 0;

  /**
   * @brief Returns the diffusion of the IF neuron, i.e. in general sqrt(2 * D)
   * @return Diffusion of IF neuron, i.e. sqrt(2*D)
   */
  double diffusion() const;

  /**
   * Returns a spike train, i.e. an array with as many steps as the time frame,
   * that contains a zero if the neuron has not spiked and a 1 if it has spiked
   * in the corresponding time bin.
   * We use the Euler-Maruyama-Scheme to solve the SDE for the IF neuron an simply
   * put a 1 into the spike train array, whenever the neuron spikes.
   * @brief Returns a spike train.
   * @param time Timeframe
   * @return A spike train
   */
  std::vector<bool> get_spike_train(const Timeframe &time) const;

  /**
   * Produces a spike train, i.e. an array with as many steps as the time frame,
   * that contains a zero if the neuron has not spiked and a 1 if it has spiked
   * in the corresponding time bin.
   * We use the Euler-Maruyama-Scheme to solve the SDE for the IF neuron an simply
   * put a 1 into the spike train array, whenever the neuron spikes.
   * @brief Returns a spike train, where IF is subject to a signal.
   * @param time Timeframe
   * @param signal Signal
   * @return A spike train
   */
  std::vector<bool> get_spike_train(const Timeframe &time,
                                    const Signal &signal) const;

  /**
   * Produces a spike train, i.e. an array with as many steps as the time frame,
   * that contains a zero if the neuron has not spiked and a 1 if it has spiked
   * in the corresponding time bin.
   * We use the Euler-Maruyama-Scheme to solve the SDE for the IF neuron an simply
   * put a 1 into the spike train array, whenever the neuron spikes.
   * @brief Returns a spike train, where we consider IF with adaptation.
   * @param time Timeframe
   * @param adapt Adaptation
   * @return A spike train
   */
  std::vector<bool> get_spike_train(const Timeframe &time,
                                    const Adaptation &adapt) const;

  /**
   * Produces a spike train, i.e. an array with as many steps as the time frame,
   * that contains a zero if the neuron has not spiked and a 1 if it has spiked
   * in the corresponding time bin.
   * We use the Euler-Maruyama-Scheme to solve the SDE for the IF neuron an simply
   * put a 1 into the spike train array, whenever the neuron spikes.
   * @brief Returns a spike train, where we consider IF with adaptation, that is
   * also subject to a signal.
   * @param time Timeframe
   * @param adapt Adaptation
   * @param signal Signal
   * @return A spike train
   */
  std::vector<bool> get_spike_train(const Timeframe &time, const Signal &signal,
                                    const Adaptation &adapt) const;

  /**
   * @brief Returns a trajectory, i.e. v(t).
   * @param [out] v Array of voltages at times given by time frame
   * @param time Timeframe
   */
  void get_voltage_curve(std::vector<double> &v, const Timeframe &time) const;

  /**
   * @brief Returns a trajectory of neuron with adaptation variable, i.e. v(t) and a(t).
   * @param [out] v Array of voltages at times given by time frame
   * @param [out] a Array of adaptation variable at times given by time frame
   * @param time Timeframe
   */
  void get_voltage_curve(std::vector<double> &v, std::vector<double> &a,
                         const Timeframe &time, const Adaptation &adapt) const;

  /**
   * @brief Setter method for mean input current.
   * @param mu Mean input current
   */
  void set_mu(double mu) { this->mu = mu; };

  /**
   * @brief Setter method for diffusion coefficient.
   * @param D
   */
  void set_D(double D) { this->D = D; };
};

#endif // IF_H
