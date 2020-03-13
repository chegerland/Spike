#ifndef WHITENOISESIGNAL_H
#define WHITENOISESIGNAL_H

#include "../Timeframe/Timeframe.h"
#include "Signal.h"
#include <string>
#include <vector>

/**
 * @class WhiteNoiseSignal
 * @brief Implements a band limited white gaussian noise signal
 */
class WhiteNoiseSignal : public Signal {
private:
  double alpha;                         ///< amplitude
  double f_low;                         ///< lower cut-off frequency
  double f_high;                        ///< higher cut-off frequency
  Timeframe time;                       ///< Timeframe
  std::vector<double> signal_values;    ///< vector containing signal values

public:

  /**
   * @brief Construct WhiteNoiseSignal from parameters
   * @param alpha Amplitude
   * @param f_low Lower cut-off frequency
   * @param f_high Higher cut-off frequency
   * @param time Time frame
   */
  WhiteNoiseSignal(double alpha, double f_low, double f_high, Timeframe time);

  /**
   * @brief Construct WhiteNoiseSignal from input file
   * @param input_file Input file in .json format
   */
  WhiteNoiseSignal(const std::string &input_file);

  /**
   * @brief Generate the white noise, i.e. fill the signal_values
   */
  void generate_white_noise();

  /**
   * @brief Update the white noise, i.e. generate it again
   */
  void update();

  /**
   * @brief Return signal, i.e. white noise at time t
   * @param t Time
   * @return Signal, i.e. white noise at time t
   */
  double signal(double t) const;
};

#endif // WHITENOISESIGNAL_H
