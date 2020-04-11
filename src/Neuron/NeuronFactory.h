/**
 * @file NeuronFactory.h
 * @author C. H. Egerland
 */

#ifndef NEURONFACTORY_H
#define NEURONFACTORY_H

#include <memory>
#include "Neuron.h"

/**
 * @class NeuronFactory
 * @brief Implements a factory pattern for neurons.
 * This class will create a specific neuron, depending on the type of neuron
 * given in an input file.
 */
class NeuronFactory {
public:
  /**
   * @brief Returns a neuron pointer.
   * Depending on the type read from the input file, this function constructs
   * the appropriate neuron.
   * @param input_file Input file in .json format
   * @return Pointer to neuron
   */
  static std::unique_ptr<Neuron> create(const std::string &input_file);
};

#endif // NEURONFACTORY_H
