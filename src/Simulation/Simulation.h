#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

//! The simulation class
/*!
* Sets up a simulation.
* Defines the input and output files, the time window and its discretization as
well as the number of times the neuron shall be simulated.
*/
class Simulation
{
public:

  /*! start time */
  double t_0;
  /*! end time */
  double t_end;
  /*! time step */
  double dt;
  /*! simulation count */
  int N;

  /*! input file */
  std::string input_file;
  /*! output file */
  std::string output_file;

  Simulation(){};
  ~Simulation(){};

  /*!
  * Constructor of simulation
  * @param a t_0
  * @param b t_end
  * @param c dt
  */
  Simulation(double a, double b, double c);

  /*!
  * Constructor of simulation
  * @param a t_0
  * @param b t_end
  * @param c dt
  * @param d N
  */
  Simulation(double a, double b, double c, int d);

};

#endif // SIMULATION_H
