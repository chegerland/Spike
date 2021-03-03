/**
 * @file SusceptibilitySimulationLin.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATIONLIN_H
#define SPIKE_SUSCEPTIBILITYSIMULATIONLIN_H

#include "Spike/Simulation/SusceptibilitySimulation.h"

namespace Spike {

/**
 * @brief A simulation where we measure the linear (first order) susceptibility
 * of an integrate-and-fire neuron.
 */
class SusceptibilitySimulationLin : public SusceptibilitySimulation {
private:
  std::vector<std::complex<double>> suscept_lin; ///< linear susceptibility

public:
  /**
   * @brief Constructs susceptibility simulation from .ini file.
   * @param input_file path to .ini file
   */
  explicit SusceptibilitySimulationLin(const std::string &input_file);

  /**
   * @brief Calculates the linear susceptibility for a given number of trials.
   * Each time the white noise signal is generated again, the neuron produces a
   * new spike train and the susceptibility is calculated. The result is then
   * added (!) to the susceptibility vector suscept_lin.
   * @param trials number of trials.
   */
  void calculate(size_t trials) override;

  /**
   * @brief Adds the susceptibility tmp_lin to suscept_lin.
   * @param tmp_lin susceptibility vector
   */
  void add_to_suscepts(const std::vector<std::complex<double>> &tmp_lin);

  /**
   * @brief Returns the size of the susceptibility vector.
   * @return size of susceptibility vector
   */
  [[nodiscard]] size_t get_size_lin() const { return suscept_lin.size(); };

  /**
   * @brief Returns the susceptibility vector.
   * @return susceptibility vector
   */
  [[nodiscard]] const std::vector<std::complex<double>> &
  get_suscept_lin() const {
    return suscept_lin;
  };
};

} // namespace Spike

#endif // SPIKE_SUSCEPTIBILITYSIMULATIONLIN_H
