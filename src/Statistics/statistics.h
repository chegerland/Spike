#ifndef STATISTICS_H
#define STATISTICS_H

#include "../Timeframe/Timeframe.h"
#include <complex>
#include <vector>

/**
 * If a neuron has spiked, add 1/dt to the corresponding entry in the firing rate.
 * @brief Adds a single spike train to the firing rate.
 * @param [in] spike_train A spike train
 * @param [in] time Timeframe
 * @param [out] firing_rate Firing rate
 */
void add_to_firing_rate(const std::vector<bool> &spike_train,
                        const Timeframe &time,
                        std::vector<double> &firing_rate);

/**
 * If a neuron has spiked add 1/(N*dt) to the corresponding entry in the firing rate.
 * @brief Adds a spike train of an ensemble of N neurons to the firing rate.
 * @param [in] spike_train A spike train
 * @param [in] time Timeframe
 * @param N Number of neurons
 * @param [out] firing_rate Firing rate
 */
void add_to_firing_rate(const std::vector<bool> &spike_train,
                        const Timeframe &time, const int N,
                        std::vector<double> &firing_rate);

/**
 * @brief Get spike times from spike train.
 * @param spike_train A spike train
 * @param time Time frame
 * @return A vectory containing the spike times.
 */
std::vector<double> get_spike_times(const std::vector<bool> &spike_train,
                                    const Timeframe &time);

/**
 * @brief Calculate the CV of some given spike times.
 * @param spike_times The spike times
 * @return The CV
 */
double calculate_cv(const std::vector<double> &spike_times);

/**
 * @brief Counts the number of spikes in a spike train.
 * @param spike_train A spike train
 * @return Number of times the neuron has spiked.
 */
int spike_count(const std::vector<bool> &spike_train);

<<<<<<< HEAD
// fourier transform firing rate
void fourier_transform_firing_rate(
=======
/**
 * @brief Fourier transform the firing rate.
 * @param [in] firing_rate Array containing the firing rate
 * @param [in] time Timeframe
 * @param [out] frequencies Array containing the frequencies
 * @param [out] firing_rate_fourier Array containing the fourier transformed firing rate
 */
void fourier_trafo_firing_rate(
>>>>>>> 17fc4e88a39ac8c59e4d5c4f86a4cebd3b9e25a8
    const std::vector<double> &firing_rate, const Timeframe &time,
    std::vector<double> &frequencies,
    std::vector<std::complex<double>> &firing_rate_fourier);

#endif // STATISTICS_H
