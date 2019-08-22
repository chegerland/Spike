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

  double t_0, t_end, dt; // Simulation parameters
  int N;
  std::string input_file;
  std::string output_file;

  // constructors
  Simulation(){};
  Simulation(double a, double b, double c);
  Simulation(double a, double b, double c, int d);

  ~Simulation(){};

  /*!
  * Sets input and output file of the simulation
  */
  void check_files();

  /*!
  * Sets input and output file of the simulation
  */
  void set_files();

};

#endif // SIMULATION_H
