#ifndef RATE_H
#define RATE_H

#include <vector>
#include <math.h>

//! Firing rate calculated using sliding window function
/*!
* Returns firing rate of a given spike train codefied by a vector of the spike times.
* It is calculated using a sliding window function with the width dt as described in \cite dayan05 (page 13, eqs. 1.8 and 1.9)
* @params t time at which the rate shall be evaluated
* @params spike_times single spike train
* @params dt time frame
*/
double firing_rate(double t, const std::vector<double> &spike_times, double dt);

#endif // RATE_H
