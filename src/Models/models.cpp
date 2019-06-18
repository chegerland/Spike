#include <math.h>
#include <random>
#include <iostream>
#include <fstream>
#include "models.h"

// Returns the voltage curve of an integrate and fire neuron by putting the
// values into separate vectors.
void voltage_curve(IF *neuron, std::vector<double> &t, std::vector<double> &v)
{
    // initial values
    v.push_back(0);
    t.push_back(neuron->t_0);

    double dt = (double)(neuron->t_end - neuron->t_0) / neuron->N; // time step

    // random numbers
    std::random_device rd{};
    std::mt19937 generator{rd()};
    std::normal_distribution<double> dist(0.0, sqrt(dt));

    // euler maruyama scheme
    double nextStep = 0;

    for (int i = 0; i < neuron->N - 1; i++)
    {
        t.push_back(t[i] + dt);
        nextStep = v[i] + neuron->drift(v[i], t[i]) * dt + neuron->diffusion(v[i], t[i]) * dist(generator);

        // reset rule
        if (nextStep > 1)
        {
            v.push_back(0);
        }
        else
        {
            v.push_back(nextStep);
        }
    }
};

// Returns a vector containing the spike times.
void spike_times(IF *neuron, std::vector<double> &spikes)
{
    // initial values
    double t;
    double v;
    v = 0;
    t = neuron->t_0;

    double dt = (double)(neuron->t_end - neuron->t_0) / neuron->N; // time step

    // random numbers
    std::random_device rd{};
    std::mt19937 generator{rd()};
    std::normal_distribution<double> dist(0.0, sqrt(dt));

    // euler maruyama scheme
    double nextStep = 0;
    for (int i = 0; i < neuron->N - 1; i++)
    {
        t += dt;
        nextStep = v + neuron->drift(v, t) * dt + neuron->diffusion(v, t) * dist(generator);

        // reset rule
        if (v > 1)
        {
            v = 0;
            spikes.push_back(t);
        }
        else
        {
            v = nextStep;
        }
    }
};

// Returns a vector containing the spike train.
void spike_train(IF *neuron, std::vector<double> &spikes)
{
    // initial values
    double t;
    double v;
    v = 0;
    t = neuron->t_0;

    double dt = (double)(neuron->t_end - neuron->t_0) / neuron->N; // time step

    // random numbers
    std::random_device rd{};
    std::mt19937 generator{rd()};
    std::normal_distribution<double> dist(0.0, sqrt(dt));

    // euler maruyama scheme
    double nextStep = 0;
    for (int i = 0; i < neuron->N - 1; i++)
    {
        t += dt;
        nextStep = v + neuron->drift(v, t) * dt + neuron->diffusion(v, t) * dist(generator);

        // reset rule
        if (v > 1)
        {
            v = 0;
            spikes.push_back(1);
        }
        else
        {
            v = nextStep;
            spikes.push_back(0);
        }
    }
};

// Returns the firing rate at time t.
// We need the spiking times and the time step for that.
double firing_rate(double t, const std::vector<double> &spike_times, double dt)
{
    // loop over the spike times 
    double rate = 0;
    for (int i = 0; i < spike_times.size(); i++)
    {
        // stepping function
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
