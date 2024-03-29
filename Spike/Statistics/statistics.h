#ifndef SPIKE_STATISTICS_H
#define SPIKE_STATISTICS_H

#include <fftw3.h>

#include <complex>
#include <vector>

#include "Spike/Signal/Signal.h"
#include "Spike/Signal/WhiteNoiseSignal.h"
#include "Spike/SpikeTrain/SpikeTrain.h"
#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

double mean(const std::vector<double> &array);

double standard_deviation(const std::vector<double> &array);

std::vector<double> get_spike_times(const SpikeTrain &spike_train,
                                    const TimeFrame &time);

double calculate_cv(const std::vector<double> &spike_times);

void cross_spectrum(const std::vector<double> &input_signal,
                    const std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::complex<double> *spectrum);

void power_spectrum(const std::vector<double> &signal,
                    const TimeFrame &time_frame, std::vector<double> &spectrum);

void susceptibility(const std::vector<double> &input_signal,
                    const std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::vector<std::complex<double>> &suscept);

void susceptibility(const WhiteNoiseSignal &signal,
                    const std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::vector<std::complex<double>> &suscept, size_t norm);

void susceptibility_lin_nonlin(const WhiteNoiseSignal &signal, 
                               const std::vector<double> &output_signal,
                               const TimeFrame &time_frame, 
                               std::vector<std::complex<double>> &suscept_lin, 
                               std::vector<std::complex<double>> &suscept_nonlin_diag, 
                               std::vector<std::complex<double>> &suscept_nonlin_antidiag, 
                               size_t norm);

void susceptibility_nonlin(
    const WhiteNoiseSignal &signal, const std::vector<double> &output_signal,
    const TimeFrame &time_frame,
    std::vector<std::vector<std::complex<double>>> &suscept_nonlin,
    size_t norm);

}  // namespace Spike

#endif  // SPIKE_STATISTICS_H
