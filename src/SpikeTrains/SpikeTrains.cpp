#include <iostream>
#include <math.h>
#include <fftw3.h>

#include "SpikeTrains.h"

#include "../Options/Options.h"

SpikeTrains::SpikeTrains(Timeframe *time, std::vector< std::vector<double> > input)
{
    this->time = time;
    trains = input;
}

SpikeTrains::SpikeTrains(std::string input_file)
{
  trains_file = input_file.substr(0,input_file.find_last_of('.'))+".out";
  time = new Timeframe(input_file);
  trains = file_to_vector(trains_file);
};

std::vector<double> SpikeTrains::isi_single(std::vector<double> train)
{
  std::vector<double> isi;

  for (int i = 1; i < train.size(); i++)
  {
      isi.push_back(train[i] - train[i-1]);
  };

  return isi;
};


double SpikeTrains::rate_single(double t, std::vector<double> train, double bin)
{
  // loop over the spike times
  double rate = 0;
  for (int i = 0; i < train.size(); i++)
  {
    // window function
    if (-bin / 2 <= (t - train[i]) && (t - train[i]) < bin / 2)
    {
      rate += 1.0 / bin;
    }
    else
    {
      rate += 0.0;
    };
  };

  return rate;
};

std::vector<double> SpikeTrains::interspike_intervals()
{
    std::vector<double> isi_ensemble;

    #pragma omp parallel for
    for (int i = 0; i < this->trains.size(); i++)
    {
      std::vector<double> isi_train;
      isi_train = isi_single(this->trains[i]);
      for (int j = 0; j < isi_train.size(); j++)
      {
        #pragma omp critical
        isi_ensemble.push_back(isi_train[j]);
      };
      isi_train.clear();
    };

    return isi_ensemble;
};

std::vector<double> SpikeTrains::firing_rate(Timeframe *times, double bin)
{
    std::vector<double> rate_ensemble;

    double t = times->t_0;

    while (t < times->t_end)
    {
      // calculate ensemle rate at time t
      double rate_trains = 0;
      for (int i = 0; i < trains.size(); i++)
      {
        rate_trains += 1.0/trains.size() * rate_single(t, trains[i], bin);
      };

      rate_ensemble.push_back(rate_trains);

      // new time step
      t += times->dt;
    };

    return rate_ensemble;
};


std::vector<std::complex<double> > SpikeTrains::susceptibility(double dt)
{
  // get firing rate
  std::vector<double> rate = this->firing_rate(this->time, dt);
  int N = rate.size();

  // define arrays needed for fftw
  double in[N];
  fftw_complex out[N];

  // fill input array with rate
  for (int i = 0; i < N; i++)
  {
    in[i] = rate[i];
  }

  fftw_plan plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
  fftw_execute(plan);

  std::vector<std::complex<double> > sus;
  for (int i = 0; i < N; i++)
  {
    std::complex<double> temp(out[i][0], out[i][1]);
    sus.push_back(temp);
  };

  fftw_destroy_plan(plan);
  fftw_cleanup();

  return sus;


};


void SpikeTrains::print_spike_trains()
{
    for (int i = 0; i < trains.size(); i++)
    {
      for (int j = 0; j < trains[i].size()-1; j++)
      {
        std::cout << trains[i][j] << " ";
      }
      std::cout << trains[i][trains[i].size()-1] << std::endl;
    };
};
