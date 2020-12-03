/**
 * @file SusceptibilitySimulationLin.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATIONLIN_H
#define SPIKE_SUSCEPTIBILITYSIMULATIONLIN_H

#include "Spike/Simulation/SusceptibilitySimulation.h"

namespace Spike {

class SusceptibilitySimulationLin : public SusceptibilitySimulation {
private:
  std::vector<std::complex<double>> suscept_lin; ///< linear susceptibility

public:
 explicit SusceptibilitySimulationLin(const std::string &input_file);
 void calculate(size_t trials) override;
 void add_to_suscepts(const std::vector<std::complex<double>> &tmp_lin);

  // getter
  [[nodiscard]] size_t get_size_lin() const { return suscept_lin.size(); };
  [[nodiscard]] const std::vector<std::complex<double>> &get_suscept_lin() const {
    return suscept_lin;
  };
};

}

#endif // SPIKE_SUSCEPTIBILITYSIMULATIONLIN_H
