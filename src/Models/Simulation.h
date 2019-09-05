#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>

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

  /*! input file containing parameters */
  std::string parameters_file;

  /*! output file containing the spike times*/
  std::string spike_times_file;

  /*! vector of vectors containing the spike trains of all N neurons */
  std::vector< std::vector<double> > spike_trains;

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

  /*!
  * Constructor of simulation
  * @param input_file Input .json file containing parameters
  */
  Simulation(std::string parameters_file);

  /*!
  * Print parameters to standard output
  */
  void print_parameters();

};

#endif // SIMULATION_H
