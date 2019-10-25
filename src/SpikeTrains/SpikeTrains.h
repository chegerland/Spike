#ifndef SPIKETRAINS_H
#define SPIKETRAINS_H

#include <string>
#include <vector>
#include <complex>

#include "../Simulation/Timeframe.h"


//! A class defining spike trains
class SpikeTrains
{
private:

  /* the time frame */
  Timeframe *time;

  /* the actual spike trains */
  std::vector< std::vector<double> > trains;

public:

  /* file containing the spike trains*/
  std::string trains_file;

  SpikeTrains(Timeframe *time, std::vector< std::vector<double> > input);
  SpikeTrains(std::string input_file);

  /* functions for single spike train */
  std::vector<double> isi_single(std::vector<double> train);
  double rate_single(double t, std::vector<double> train, double bin);

  /* functions for ensemble */
  std::vector<double> interspike_intervals();
  std::vector<double> firing_rate(Timeframe *time, double bin);

  std::vector<std::complex<double> > susceptibility(double dt);

  /* print function */
  void print_spike_trains();
};

#endif // SPIKETRAINS_H
