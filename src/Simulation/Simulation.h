#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

#include "Timeframe.h"
#include "../Neuron/Neuron.h"
#include "../Signal/Signal.h"


//! The simulation class
/*!
* Sets up a simulation.
* Defines the input and output files, the time window and its discretization as
well as the number of times the neuron shall be simulated.
*/
class Simulation
{
private:

  /* a time frame */
  Timeframe *time;

  /* the neuron to simulate */
  Neuron *neuron;

  /* number of times the neuron shall be simulated */
  unsigned N;

  /* the signal applied to the neuron */
  Signal *signal;

  /*! input file containing parameters */
  std::string parameters;

public:

  /*!
  * Constructor of simulation
  * @param input_file Input .json file containing parameters
  */
  Simulation(std::string input_file);


  void simulate() const;

  /*!
  * Print parameters to standard output
  */
  void print_parameters();

};

#endif // SIMULATION_H
