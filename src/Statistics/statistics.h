#ifndef STATISTICS_H
#define STATISTICS_H

#include <armadillo>
#include <complex>
#include <fftw3.h>
#include <vector>

#include "../Signal/Signal.h"
#include "../Signal/WhiteNoiseSignal.h"
#include "../SpikeTrain/SpikeTrain.h"
#include "../TimeFrame/TimeFrame.h"

double mean(const std::vector<double> &array, const size_t length);

double standard_deviation(const std::vector<double> &array,
                          const size_t length);

std::vector<double> get_spike_times(const SpikeTrain &spike_train,
                                    const TimeFrame &time);

double calculate_cv(const std::vector<double> &spike_times);

void cross_spectrum(std::vector<double> &input_signal,
                    std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::complex<double> *spectrum);

void power_spectrum(std::vector<double> &signal, const TimeFrame &time_frame,
                    std::vector<double> &spectrum);

void susceptibility(std::vector<double> &input_signal,
                    std::vector<double> &output_signal,
                    const TimeFrame &time_frame,
                    std::vector<std::complex<double>> &suscept);

void susceptibility(const std::shared_ptr<WhiteNoiseSignal> &signal,
                    const std::vector<double> &output_signal,
                    const std::shared_ptr<const TimeFrame> &time_frame,
                    std::vector<std::complex<double>> &suscept);

void susceptibility_nonlinear_diag(std::vector<double> &input_signal,
                                   std::vector<double> &output_signal,
                                   const TimeFrame &time_frame,
                                   std::vector<std::complex<double>> &suscept);

void susceptibility_nonlinear_diag(const std::shared_ptr<WhiteNoiseSignal> &signal,
                                   const std::vector<double> &output_signal,
                                   const std::shared_ptr<const TimeFrame> &time_frame,
                                   std::vector<std::complex<double>> &suscept);

void add_spike_train_to_kernel(const SpikeTrain &spike_train,
                               const Signal &signal,
                               const TimeFrame &time_frame, double norm,
                               double *kernel);

#endif // STATISTICS_H
