/**
 * @file SusceptibilitySimulationNonlin.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATIONNONLIN_H
#define SPIKE_SUSCEPTIBILITYSIMULATIONNONLIN_H

#include "Spike/Simulation/SusceptibilitySimulation.h"

namespace Spike {

class SusceptibilitySimulationNonlin : public SusceptibilitySimulation {
private:
  std::vector<std::vector<std::complex<double>>>
      suscept_nonlin; ///< nonlinear susceptibility

public:
  explicit SusceptibilitySimulationNonlin(const std::string &input_file);
  void calculate(size_t trials) override;
  void add_to_suscepts(const std::vector<std::vector<std::complex<double>>> &tmp_nonlin);

  // getter
  //[[nodiscard]] size_t get_size_lin() const { return suscept_lin.size(); };
  [[nodiscard]] size_t get_size_nonlin() const { return suscept_nonlin.size(); };
  [[nodiscard]] const std::vector<std::vector<std::complex<double>>> &get_suscept_nonlin() const {
    return suscept_nonlin;
  };
};

}

#endif // SPIKE_SUSCEPTIBILITYSIMULATIONNONLIN_H
