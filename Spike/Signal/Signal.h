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
   * @brief Virtual destructor
   */
  virtual ~Signal() = default;

  [[nodiscard]] double get_value(size_t i) const;

  virtual void print(std::ostream &out) const = 0;
  friend std::ostream &operator<<(std::ostream &out, const Signal &signal);
};

} // namespace Spike

#endif // SPIKE_SIGNAL_H
