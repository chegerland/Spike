/**
 * @file Signal.h
 * @author C. H. Egerland
 */

#ifndef SPIKE_SIGNAL_H
#define SPIKE_SIGNAL_H

#include <memory>
#include <ostream>
#include <string>

#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

/**
 * @brief An abstract base class for signals.
 */
class Signal {
protected:
  const TimeFrame &time_frame;       ///< reference to time frame
  std::vector<double> signal_values; ///< array containing the signal values

public:
  /**
   * @brief Constructs signal from given time frame.
   * @param time_frame Time frame
   */
  explicit Signal(const TimeFrame &time_frame);

  /**
   * @brief Returns the signal value at index i.
   * @param i time index
   * @return signal value
   */
  [[nodiscard]] double get_value(size_t i) const;

  /**
   * @brief Prints the signal to out stream.
   * @param out out stream
   */
  virtual void print(std::ostream &out) const = 0;

  /**
   * @brief Overloads the << operator so we can print signal to out.
   * @param out out stream
   * @param signal signal
   * @return out stream
   */
  friend std::ostream &operator<<(std::ostream &out, const Signal &signal);
};

} // namespace Spike

#endif // SPIKE_SIGNAL_H
