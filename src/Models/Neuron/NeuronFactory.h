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
  static Neuron *create(std::string input_file);

};

#endif // NEURONFACTORY_H
