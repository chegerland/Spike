/**
 * @file NeuronFactory.h
 * @author C. H. Egerland
 */

#ifndef SPIKE_NEURONFACTORY_H
#define SPIKE_NEURONFACTORY_H

#include "Spike/Neuron/IF.h"
#include <memory>

namespace Spike {

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
  static std::unique_ptr<IF> create(const std::string &input_file);
};

} // namespace Spike

#endif // SPIKE_NEURONFACTORY_H
