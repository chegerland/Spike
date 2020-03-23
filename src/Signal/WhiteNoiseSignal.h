#ifndef WHITENOISESIGNAL_H
#define WHITENOISESIGNAL_H

#include "../TimeFrame/TimeFrame.h"
#include "Signal.h"
#include <string>
#include <vector>

/**
 * @class WhiteNoiseSignal
 * @brief Implements a band limited white gaussian noise get_value
 */
class WhiteNoiseSignal : public Signal {
private:
  double alpha;                      ///< amplitude
  double f_low;                      ///< lower cut-off frequency
  double f_high;                     ///< higher cut-off frequency

public:
  /**
   * @brief Construct WhiteNoiseSignal from parameters
   * @param alpha Amplitude
   * @param f_low Lower cut-off frequency
   * @param f_high Higher cut-off frequency
   * @param time Time frame
   */
  WhiteNoiseSignal(double alpha, double f_low, double f_high,
                   const TimeFrame &time_frame);

  /**
   * @brief Construct WhiteNoiseSignal from input file
   * @param input_file Input file in .json format
   */
  WhiteNoiseSignal(const std::string &input_file, const TimeFrame& time_frame);

  /**
   * @brief Generate the white noise, i.e. fill the signal_values
   */
  void calculate_signal();

  /**
   * @brief Return get_value, i.e. white noise at time t
   * @param t Time
   * @return Signal, i.e. white noise at time t
   */
  double signal(double t) const;
};

#endif // WHITENOISESIGNAL_H
