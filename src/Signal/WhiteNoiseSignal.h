#ifndef WHITENOISESIGNAL_H
#define WHITENOISESIGNAL_H

#include "../Timeframe/Timeframe.h"
#include "Signal.h"
#include <string>
#include <vector>

class WhiteNoiseSignal : public Signal {
private:
  double alpha;   // amplitude
  double cut_off; // cut-off frequency
  Timeframe time;
  std::vector<double> signal_values;

public:
  // constructors
  WhiteNoiseSignal(double alpha, double cut_off, Timeframe time);
  explicit WhiteNoiseSignal(const std::string &input_file);

  // generate the white noise signal
  void generate_white_noise();

  // return signal
  double signal(double t) const override;
};

#endif // WHITENOISESIGNAL_H
