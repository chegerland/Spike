#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>

// spike libraries
#include "Spike.h"

// main
int main(int argc, char *argv[])
{
  /*
  Timeframe *time;
  time = new Timeframe(0, 10, 1e-3);

  std::vector< std::vector<double> > input = { {0, 1, 3, 3.2, 4}, {0.2, 1.4, 2}, {4, 8, 9}};

  SpikeTrains *trains;
  trains = new SpikeTrains(time, input);

  std::cout << "Printing spike train." << std::endl;
  trains->print_spike_trains();

  std::cout << "Printing ISIs." << std::endl;
  std::vector<double> isi = trains->interspike_intervals();
  for (int i = 0; i < isi.size(); i++)
  {
    std::cout << isi[i] << std::endl;
  }
  */

  /*
  // read command line options
  Options *options;
  options = new Options(argc, argv);

  SpikeTrains *trains;
  trains = new SpikeTrains(options->file);

  // make output file for isi
  std::ofstream file;
  std::string name = trains->trains_file.substr(0, trains->trains_file.find_last_of('.'))+".isi";
  file.open(name);

  std::vector<double> isi = trains->interspike_intervals();
  for (int i = 0; i < isi.size(); i++)
  {
    file << isi[i] << std::endl;
  };

  file.close();
  */


  // read command line options
  Options *options;
  options = new Options(argc, argv);

  SpikeTrains *trains;
  trains = new SpikeTrains(options->file);

  // calculate rate
  Timeframe *time;
  time = new Timeframe(0, 40, 1e-2);
  std::vector<double> rate = trains->firing_rate(time, 1e-3);

  // push rate to file
  std::ofstream file;
  std::string name = trains->trains_file.substr(0, trains->trains_file.find_last_of('.'))+".rate";
  file.open(name);
  for (int i = 0; i < rate.size(); i++)
  {
    file << rate[i] << std::endl;
  };

  file.close();


/*
  // read command line options
  Options *options;
  options = new Options(argc, argv);

  SpikeTrains *trains;
  trains = new SpikeTrains(options->file);

  std::ofstream file;
  std::string name = trains->trains_file.substr(0, trains->trains_file.find_last_of('.'))+".susc";
  file.open(name);

  std::vector<std::complex<double>> sus = trains->susceptibility(0.9);
  for (int i = 0; i < sus.size(); i++)
  {
    file << real(sus[i]) << " " << imag(sus[i]) << std::endl;
  };

  file.close();
*/



};
