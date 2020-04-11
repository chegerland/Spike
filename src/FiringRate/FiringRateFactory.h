/**
 * @file FiringRateFactory.h
 * @author C. H. Egerland
 */

#ifndef FIRINGRATEFACTORY_H
#define FIRINGRATEFACTORY_H

#include "FiringRate.h"
#include <memory>

/**
 * @class FiringRateFactory
 * @brief Factoy class for firing rates.
 * This class will create a specific firing rate, depending on the type of
 * firing rate given in a input file.
 */
class FiringRateFactory {
public:
  /**
   * @brief Returns a firing rate pointer.
   * Depending on the type read from the input file, this function constructs
   * the appropriate firing rate.
   * @param input_file Input file in .json format
   * @param time_frame Time frame
   * @return Pointer to firing rate
   */
  static std::unique_ptr<FiringRate> create(const std::string &input_file,
                                            const TimeFrame &time_frame);
};

#endif // FIRINGRATEFACTORY_H
