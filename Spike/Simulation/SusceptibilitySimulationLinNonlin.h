/**
 * @file SusceptibilitySimulationLinNonlin.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATIONLINNONLIN_H
#define SPIKE_SUSCEPTIBILITYSIMULATIONLINNONLIN_H

#include "Spike/Simulation/SusceptibilitySimulation.h"

namespace Spike {

class SusceptibilitySimulationLinNonlin : public SusceptibilitySimulation {
private:
  std::vector<std::complex<double>> suscept_lin; ///< linear susceptibility
  std::vector<std::complex<double>>
      suscept_nonlin; ///< nonlinear susceptibility

public:
 explicit SusceptibilitySimulationLinNonlin(const std::string &input_file);
 void calculate(int trials) override;
 void add_to_suscepts(const std::vector<std::complex<double>> &tmp_lin,
                       const std::vector<std::complex<double>> &tmp_nonlin);

  // getter
  [[nodiscard]] size_t get_size_lin() const { return suscept_lin.size(); };
  [[nodiscard]] size_t get_size_nonlin() const { return suscept_nonlin.size(); };
  [[nodiscard]] const std::vector<std::complex<double>> &get_suscept_lin() const {
    return suscept_lin;
  };
  [[nodiscard]] const std::vector<std::complex<double>> &get_suscept_nonlin() const {
    return suscept_nonlin;
  };
};

}

#endif // SPIKE_SUSCEPTIBILITYSIMULATIONLINNONLIN_H
