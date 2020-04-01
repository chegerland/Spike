/**
 * @file FiringRateExp.h
 * @author C. H. Egerland
 */
#ifndef FIRINGRATEEXP_H
#define FIRINGRATEEXP_H

#include "FiringRate.h"

/**
 * @class FiringRateExp
 * @brief Implements an exponential firing rate.
 * The exponential firing rate is calculated by convolving the spike train with
 * a gaussian window function. See @cite dayan05
 */
class FiringRateExp : public FiringRate {
private:
  double res; ///< resolution
public:
  /**
   * @brief Constructs an exponential firing rate from a .json input file and a
   * given time frame.
   * @param input_file Input file in .json format
   * @param time_frame Time frame
   */
  FiringRateExp(const std::string &input_file, const TimeFrame &time_frame);

  /**
   * @brief Constructs an exponential firing rate from a given time frame.
   * @param time_frame Time frame
   * @param res Resolution
   */
  FiringRateExp(const TimeFrame &time_frame, double res);

  /**
   * @brief Calculates the exponential firing rate.
   * Computes the convolution of a gaussian window function with the spike train.
   */
  void calculate() override;
};

#endif // FIRINGRATEEXP_H
