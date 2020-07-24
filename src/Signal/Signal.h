/**
 * @file Signal.h
 * @author C. H. Egerland
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#include <memory>
#include <string>
#include <ostream>

#include "../src/TimeFrame/TimeFrame.h"

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

  virtual void print(std::ostream& out) const = 0;
  friend std::ostream& operator<< (std::ostream &out, const Signal &signal);
};

#endif // SIGNAL_H
