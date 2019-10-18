#ifndef IFADAPT_H
#define IFADAPT_H

#include <math.h>
#include <vector>

#include "../Neuron/Neuron.h"

/*!
* Implements a generic integrate and fire neuron with adaption.
*/
class IFadapt : public Neuron
{
protected:

  /*! Mobility */
  double mu;

  /*! Diffusion coefficient */
  double D;

  /*! Adaption strength */
  double Delta;

  /*! Adaption time scale */
  double tau_a;

public:

  /*!
  * Returns the drift of a generic IFadapt model.
  * Is implemented by specific IFadapt model
  * @param v Voltage
  * @param t Time
  */
  virtual double drift(double v, double t) const =0;

  /*!
  * Returns the diffusion of the IFadapt models which is the same for all of them.
  * @param v Voltage
  * @param t Time
  */
  double diffusion(double v, double t) const;

  /*!
  * Returns the times at which the IFadapt neuron has spiked and puts them into a vector.
  * @param spikes Vector to put the spike times into
  * @param simulation simulation class containing information on the time frame etc.
  */
  void spike_times(std::vector<double> &spikes, Simulation *simulation) const;

  /*!
  * Prints the voltage curve, i.e. the function v(t) and a(t) into an output file specified by the simulation
  * @param simulation simulation class containing information on the time frame etc.
  */
  void voltage_curve(Simulation *simulation) const;

  /*!
  * Prints the limit cycle for the deterministic case into an output file specified by the simulation
  * @param simulation simulation class containing information on the time frame etc.
  */
  virtual void limit_cycle(Simulation *simulation) =0;

};

#endif // IFADAPT_H
