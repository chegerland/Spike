#ifndef WHITENOISESIGNAL_H
#define WHITENOISESIGNAL_H

#include "../TimeFrame/TimeFrame.h"
#include "Signal.h"
#include <complex>
#include <random>
#include <string>
#include <vector>

/**
 * @class WhiteNoiseSignal
 * @brief Implements a band limited white gaussian noise get_value
 */
class WhiteNoiseSignal : public Signal {
private:
  double alpha;  ///< amplitude
  double f_low;  ///< lower cut-off frequency
  double f_high; ///< higher cut-off frequency

  std::vector<std::complex<double>> frequencies;

  std::random_device rd;
  std::mt19937 generator;
  std::normal_distribution<double> dist;

public:
  /**
   * @brief Construct WhiteNoiseSignal from parameters
   * @param alpha Amplitude
   * @param f_low Lower cut-off frequency
   * @param f_high Higher cut-off frequency
   * @param time Time frame
   */
  WhiteNoiseSignal(double alpha, double f_low, double f_high,
                   const std::shared_ptr<const TimeFrame> &time_frame);

  /**
   * @brief Construct WhiteNoiseSignal from input file
   * @param input_file Input file in .json format
   */
  WhiteNoiseSignal(const std::string &input_file,
                   const std::shared_ptr<const TimeFrame> &time_frame);

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

  const std::vector<double> &get_values() const { return signal_values; };
  const std::vector<std::complex<double>> &get_frequencies() const {
    return frequencies;
  };

  double get_alpha() const { return alpha; };
  double get_variance() const { return 2. * (f_high - f_low) * alpha; };

  void print_info(std::ofstream &file) const override;
};

#endif // WHITENOISESIGNAL_H
