/**
 * @file FiringRateBox.h
 * @author C. H. Egerland
 */

#ifndef FIRINGRATEBOX_H
#define FIRINGRATEBOX_H

#include "FiringRate.h"

/**
 * @class FiringRateBox
 * @brief Implements a box firing rate.
 * The box firing rate is calculated by counting the number of neuron that have
 * spiked in a certain time interval (here given by the time step dt of the time
 * frame) and dividing that number by N*dt, where N is the number of neurons
 * overall.
 */
class FiringRateBox : public FiringRate {
public:
  /**
   * @brief Constructs a box firing rate from a .json input file and a given
   * time frame.
   * @param input_file Input file in .json format
   * @param time_frame Time frame
   */
  FiringRateBox(const std::string &input_file, const TimeFrame &time_frame);

  /**
   * @brief Constructs a box firing rate from a given time frame.
   * @param time_frame
   */
  explicit FiringRateBox(const TimeFrame &time_frame);

  /**
   * @brief Calculates the box firing rate.
   * The firing rate value at position i is given by the spike histogram value
   * at position i divided by N*dt.
   */
  void calculate() override;

  /**
   * @brief Prints the firing rate parameters to a given file.
   * @param file File stream.
   */
  void print_info(std::ofstream &file) override;
};

#endif // FIRINGRATEBOX_H
