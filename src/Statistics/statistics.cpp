#include "statistics.h"

// firing rate with sliding window function
double firing_rate(double t, const std::vector<double> &spike_times, double dt)
{
    // loop over the spike times 
    double rate = 0;
    for (int i = 0; i < spike_times.size(); i++)
    {
        // window function
        if (-dt / 2 <= (t - spike_times[i]) && (t - spike_times[i]) < dt / 2)
        {
            rate += 1 / dt;
        }
        else
        {
            rate += 0;
        }
    }

    return rate;
};
