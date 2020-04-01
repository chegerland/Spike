#ifndef STATISTICS_H
#define STATISTICS_H

#include <complex>
#include <fftw3.h>
#include <vector>

#include "../SpikeTrain/SpikeTrain.h"
#include "../TimeFrame/TimeFrame.h"

double mean(const double *array, const int length);

double standard_deviation(const double *array, const int length);

std::vector<double> get_spike_times(const SpikeTrain &spike_train,
                                    const TimeFrame &time);

double calculate_cv(const std::vector<double> &spike_times);

void shorten_array(const double *array_long, const TimeFrame &time_frame_long,
                   const TimeFrame &time_frame_short, double *array_short);

void cross_spectrum(double *input_signal, double *output_signal,
                    const TimeFrame &time_frame, fftw_complex *spectrum);

void power_spectrum(double *signal, const TimeFrame &time_frame,
                    double *spectrum);

void susceptibility(double *input_signal, double *output_signal,
                    const TimeFrame &time_frame, fftw_complex *suscept);

#endif // STATISTICS_H
