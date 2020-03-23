#ifndef SIGNALFACTORY_H
#define SIGNALFACTORY_H

#include <string>

#include "Signal.h"
#include "../src/TimeFrame/TimeFrame.h"

/**
 * @class SignalFactory
 * @brief Implements the factory design pattern for Signal.
 */
class SignalFactory {
public:
  /**
   * Returns a pointer to a get_value, depending on the type read from input file
   * @param input_file Input file in .json format
   * @return Pointer to get_value
   */
  static Signal * create(const std::string& input_file, const TimeFrame& time_frame);
};

#endif // SIGNALFACTORY_H
