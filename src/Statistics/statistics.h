#ifndef STATISTICS_H
#define STATISTICS_H

#include "../TimeFrame/TimeFrame.h"
#include "../SpikeTrain/SpikeTrain.h"
#include <complex>
#include <vector>

/**
 * @brief Get spike times from spike train.
 * @param spike_train A spike train
 * @param time Time frame
 * @return A vectory containing the spike times.
 */
std::vector<double> get_spike_times(const SpikeTrain &spike_train,
                                    const TimeFrame &time);

/**
 * @brief Calculate the CV of some given spike times.
 * @param spike_times The spike times
 * @return The CV
 */
double calculate_cv(const std::vector<double> &spike_times);

/**
 * @brief Fourier transform the firing rate.
 * @param [in] firing_rate Array containing the firing rate
 * @param [in] time TimeFrame
 * @param [out] frequencies Array containing the frequencies
 * @param [out] firing_rate_fourier Array containing the fourier transformed
 * firing rate
 */
void fourier_trafo_firing_rate(
    const std::vector<double> &firing_rate, const TimeFrame &time,
    std::vector<double> &frequencies,
    std::vector<std::complex<double>> &firing_rate_fourier);

#endif // STATISTICS_H
