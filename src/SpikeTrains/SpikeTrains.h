#ifndef SPIKETRAINS_H
#define SPIKETRAINS_H

//! A class defining spike trains
class SpikeTrains
{
private:

  /* the time frame */
  TimeFrame time;

  /* the actual spike trains */
  std::vector< std::vector<double> >;

public:

  void get_from_simulation(Simulation *sim);
  void get_from_file(std::string input_file);

  std::vector<double> interspike_intervals();
  std::vector<double> firing_rate();
};

#endif // SPIKETRAINS_H
