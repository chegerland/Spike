#include <iostream>
#include <fstream>
#include <iterator>

#include "isi.h"

// interspike intervals of a single spike train
std::vector<double> isi(const std::vector<double> spike_times)
{
    std::vector<double> interspikes;

    for (int i = 0; i < spike_times.size()-1; i++)
    {
        interspikes.push_back(spike_times[i+1] - spike_times[i]);
    };

    return interspikes;
};
