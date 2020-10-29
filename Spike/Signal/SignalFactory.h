#ifndef SPIKE_SIGNALFACTORY_H
#define SPIKE_SIGNALFACTORY_H

#include <memory>
#include <string>

#include "Spike/Signal/Signal.h"
#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

/**
 * @class SignalFactory
 * @brief Implements the factory design pattern for Signal.
 */
class SignalFactory {
public:
  /**
   * Returns a pointer to a get_value, depending on the type read from input
   * file
   * @param input_file Input file in .ini format
   * @return Pointer to get_value
   */
  static std::unique_ptr<Signal> create(const std::string &input_file,
                                        const TimeFrame &time_frame);
};

} // namespace Spike

#endif // SPIKE_SIGNALFACTORY_H
