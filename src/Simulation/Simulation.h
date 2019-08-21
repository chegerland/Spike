#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>

class Simulation
{
public:

  double t_0, t_end, dt; // Simulation parameters
  double N;
  std::string input_file;
  std::string output_file;

  Simulation(){};
  ~Simulation(){};

  Simulation(double a, double b, double c)
  {
    t_0 = a;
    t_end = b;
    dt = c;
  };

  /*!
  * Sets the parameters for the simulation
  * @param[in] a Starting time
  * @param[in] b Stop time
  * @param[in] c Time step
  */
  void set_params(double a, double b, double c) {
    this->t_0 = a;
    this->t_end = b;
    this->dt = c;
  };

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
