#ifndef SIGNALFACTORY_H
#define SIGNALFACTORY_H

#include "Signal.h"
#include <string>

/**
 * @class SignalFactory
 * @brief Implements the factory design pattern for Signal.
 */
class SignalFactory {
public:
  /**
   * Returns a pointer to a signal, depending on the type read from input file
   * @param input_file Input file in .json format
   * @return Pointer to signal
   */
  static Signal * create(const std::string& input_file);
};

#endif // SIGNALFACTORY_H
