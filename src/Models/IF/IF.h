#ifndef IF_H
#define IF_H

#include <math.h>
#include <vector>

#include "../neuron.h"

//! A generic integrate and fire model.
/*!
 * Implements a generic integrate and fire (IF) neuron, which per default is an perfect integrate and fire model.
 * This is the superclass of the family of IF neurons, therefore the drift term can be changed by its subclasses.
 * Through a simulation we obtain the spike times or voltage curve from this class.
 * We can also check the analytic result for the firing rate.
 */
class IF : public Neuron {
  protected:
    double mu, D;

  public:

    /*!
     * Sets the model parameters for a generic IF model
     * @param[in] a mu
     * @param[in] b D
     */
    void set_if_params(double a, double b) {
      this->mu = a;
      this->D = b;
    };

    /*!
     * Returns the drift of a generic IF model.
     * Is implemented by specific IF model
     * @param[in] v Voltage
     * @param[in] t Time
     */
    virtual double drift(double v, double t) const =0;

    /*!
     * Returns the diffusion of the IF models which is the same for all of them.
     * @param[in] v Voltage
     * @param[in] t Time
     */
    double diffusion(double v, double t) const {
      return sqrt(2*this->D);
    };

    /*!
     * Returns the voltage curve of a generic IF neuron;
     * NOT IMPLEMENTED YET!
     */
    void voltage_curve() const;

    /*!
     * Returns the times at which the IF neuron has spiked and puts them into a vector.
     * @param[in] spikes Vector to put the spike times into
     */
    void spike_times(
        std::vector<double> &spikes,
        Simulation *simulation
        ) const;
};

#endif // IF_H
