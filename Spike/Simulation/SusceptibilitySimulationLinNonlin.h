/**
 * @file SusceptibilitySimulationLinNonlin.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATIONLINNONLIN_H
#define SPIKE_SUSCEPTIBILITYSIMULATIONLINNONLIN_H

#include "Spike/Simulation/SusceptibilitySimulation.h"

namespace Spike {

/**
 * @brief A simulation where we measure the linear (first order) susceptibility
 * as well as the diagonal second order susceptibility of an integrate-and-fire
 * neuron.
 */
class SusceptibilitySimulationLinNonlin : public SusceptibilitySimulation {
   private:
    std::vector<std::complex<double>> suscept_lin;  ///< linear susceptibility
    std::vector<std::complex<double>>
        suscept_nonlin;  ///< linear susceptibility

   public:
    /**
     * @brief Constructs susceptibility simulation from .ini file.
     * @param input_file path to .ini file
     */
    explicit SusceptibilitySimulationLinNonlin(const std::string &input_file);

    /**
     * @brief Calculates the linear susceptibility and the diagonal second order
     * susceptibility for a given number of trials. Each time the white noise
     * signal is generated again, the neuron produces a new spike train and the
     * susceptibility is calculated. The result is then added (!) to the
     * susceptibility vector suscept_lin.
     * @param trials number of trials.
     */
    void calculate(size_t trials) override;

    /**
     * @brief Adds the susceptibility tmp_lin to suscept_lin.
     * @param tmp_lin susceptibility vector
     */
    void add_to_suscepts(const std::vector<std::complex<double>> &tmp_lin, const std::vector<std::complex<double>> &tmp_nonlin);

    /**
     * @brief Returns the size of the linear susceptibility vector.
     * @return size of susceptibility vector
     */
    [[nodiscard]] size_t get_size_lin() const { return suscept_lin.size(); };

    /**
     * @brief Returns the size of the nonlinear susceptibility vector.
     * @return size of susceptibility vector
     */
    [[nodiscard]] size_t get_size_nonlin() const { return suscept_nonlin.size(); };

    /**
     * @brief Returns the linear susceptibility vector.
     * @return susceptibility vector
     */
    [[nodiscard]] const std::vector<std::complex<double>> &get_suscept_lin()
        const {
        return suscept_lin;
    };

    /**
     * @brief Returns the nonlinear susceptibility vector.
     * @return susceptibility vector
     */
    [[nodiscard]] const std::vector<std::complex<double>> &get_suscept_nonlin()
        const {
        return suscept_nonlin;
    };
};

}  // namespace Spike

#endif  // SPIKE_SUSCEPTIBILITYSIMULATIONLINNONLIN_H