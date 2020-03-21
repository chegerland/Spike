#ifndef STATISTICS_H
#define STATISTICS_H

#include "../Timeframe/Timeframe.h"
#include <complex>
#include <vector>

// add spike train to firing rate
void add_to_firing_rate(const std::vector<bool> &spike_train,
                        const Timeframe &time,
                        std::vector<double> &firing_rate);
void add_to_firing_rate(const std::vector<bool> &spike_train,
                        const Timeframe &time, const int N,
                        std::vector<double> &firing_rate);

// calculate spike times
std::vector<double> get_spike_times(const std::vector<bool> &spike_train,
                                    const Timeframe &time);

// calculate cv
double calculate_cv(const std::vector<double> &spike_times);

// count the spikes
int spike_count(const std::vector<bool> &spike_train);

// fourier transform firing rate
void fourier_transform_firing_rate(
    const std::vector<double> &firing_rate, const Timeframe &time,
    std::vector<double> &frequencies,
    std::vector<std::complex<double>> &firing_rate_fourier);

#endif // STATISTICS_H
