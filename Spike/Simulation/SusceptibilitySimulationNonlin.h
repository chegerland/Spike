/**
 * @file SusceptibilitySimulationNonlin.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATIONNONLIN_H
#define SPIKE_SUSCEPTIBILITYSIMULATIONNONLIN_H

#include "Spike/Simulation/SusceptibilitySimulation.h"

namespace Spike {

/**
 * @brief A simulation where we measure the nonlinear (second order)
 * susceptibility of an integrate-and-fire neuron.
 */
class SusceptibilitySimulationNonlin : public SusceptibilitySimulation {
private:
  std::vector<std::vector<std::complex<double>>>
      suscept_nonlin; ///< nonlinear susceptibility

public:
  /**
   * @brief Constructs susceptibility simulation from .ini file.
   * @param input_file path to .ini file
   */
  explicit SusceptibilitySimulationNonlin(const std::string &input_file);


  /**
   * @brief Calculates the nonlinear susceptibility for a given number of trials.
   * Each time the white noise signal is generated again, the neuron produces a
   * new spike train and the susceptibility is calculated. The result is then
   * added (!) to the susceptibility matrix suscept_nonlin.
   * @param trials number of trials.
   */
  void calculate(size_t trials) override;

  /**
   * @brief Adds the susceptibility matrix tmp_nonlin to suscept_nonlin.
   * @param tmp_nonlin susceptibility matrix
   */
  void add_to_suscepts(
      const std::vector<std::vector<std::complex<double>>> &tmp_nonlin);


  /**
   * @brief Returns the size of the susceptibility matrix.
   * @return size of susceptibility matrix
   */
  [[nodiscard]] size_t get_size_nonlin() const {
    return suscept_nonlin.size();
  };


  /**
   * @brief Returns the susceptibility matrix.
   * @return susceptibility matrix
   */
  [[nodiscard]] const std::vector<std::vector<std::complex<double>>> &
  get_suscept_nonlin() const {
    return suscept_nonlin;
  };
};

} // namespace Spike

#endif // SPIKE_SUSCEPTIBILITYSIMULATIONNONLIN_H
