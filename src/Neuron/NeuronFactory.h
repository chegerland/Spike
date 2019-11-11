#ifndef NEURONFACTORY_H
#define NEURONFACTORY_H

#include <string>

#include "Neuron.h"

//! Neuron Factory
/*!
* Class that implements the factory design pattern for neurons.
*/
class NeuronFactory
{
public:

  /*!
  * Return the appropriate pointer of type Neuron for a specific neuron type indicated
  * inside the input_file.
  * @param input_file .json file containing the type of the neuron.
  */
  static Neuron *create(std::string input_file);

};

#endif // NEURONFACTORY_H
