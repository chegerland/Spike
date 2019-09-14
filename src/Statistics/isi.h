#ifndef ISI_H
#define ISI_H

#include <vector>

#include "models.h"

//! Interspike intervals of a single spike train.
/*!
* Returns the interval between two consecutive spikes.
* @params spike_times Vector containing the spike times.
*/
std::vector<double> isi(const std::vector<double> spike_times);

#endif // ISI_H
