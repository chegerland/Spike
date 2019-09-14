#include <vector>
#include <string>
#include <fstream>

// statistics
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
using namespace boost::accumulators;

// headers
#include "statistics.h"
#include "ensemble_statistics.h"

// ensemble firing rate
void ensemble_firing_rate(Simulation *sim, double dt)
{
  // declare output file
  std::string output_file = sim->spike_times_file.substr(0,sim->spike_times_file.find_last_of('.'))+"_rate.out";
  std::ofstream rate_file;
  rate_file.open(output_file);

  // push initial value
  double t;
  t = sim->t_0;
  rate_file << t << " " << 0 << std::endl;

  // define accumulator for rate
  accumulator_set<double, stats<tag::mean, tag::variance> > acc;

  // loop over time
  while (t < sim->t_end)
  {
    // new time
    t += sim->dt;

    // refresh accumulator
    acc = {};

    // loop over all spike trains, adding to firing rate
    for (int j = 0; j < sim->N; j++)
    {
        acc(firing_rate(t, sim->spike_trains[j], dt));
    };

    // push values to file
    rate_file << t << " " << mean(acc) << " " << variance(acc) << std::endl;
  };

  // close file
  rate_file.close();
};

// isi of a whole ensemble of spike times
void ensemble_isi(Simulation *sim)
{
  // declare output file
  std::string output_file = sim->spike_times_file.substr(0,sim->spike_times_file.find_last_of('.'))+"_isi.out";
  std::ofstream isi_file;
  isi_file.open(output_file);

  // dummy vector for single spike train;
  std::vector<double> spike_train;

  // push differences into file
  for (int i = 0; i <= sim->N ; i++)
  {
    // set current spike train
    spike_train = sim->spike_trains[i];

    // push all interspike intervals of spike into file
    for (int j = 1; j < spike_train.size(); j++)
    {
      isi_file << spike_train[j] - spike_train[j-1] << "\n";
    };

    // clear spike train
    spike_train.clear();
  };

  // close the interspike interval file
  isi_file.close();
};
