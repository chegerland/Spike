#include <iostream>
#include <fstream>
#include <ctime> 
#include <vector>

#include "Models/models.h"
#include "InputOutput/inputoutput.h"

// Produces firing rate plots of a perfect integrate and fire neuron from lecture 7 of neusig lecture.
void pif_neusig()
{
    // define the PIF neuron with parameters shown on slide
    IF *P = new IF();
    P->t_0 = 0;
    P->t_end = 8;
    P->N = 1000;
    P->mu = 1;
    P->D = 0.02;

    // define vector vor spiketimes, time and firing rate
    std::vector<double> spikes;
    std::vector<double> t;
    std::vector<double> rate;

    // define time scale for firing rate
    int N = 400;
    double dt = (double)(P->t_end - P->t_0) / N; // time step

    // initial values
    t.push_back(P->t_0);
    rate.push_back(0);

    // fill time and firing rate vector
    for (int j = 0; j < N; j++)
    {
        t.push_back(t[j] + dt);
        rate.push_back(0);
    }

    //clock_t begin = clock();
    
    // loop over simulation
    int Nsims = 10000;
    for (int i = 0; i < Nsims; i++)
    {
        // get spike times
        spike_times(P, spikes);

        // get firing rate for every time step, weighted with 1/Nsims
        for (int j = 0; j < N; j++)
        {
            rate[j] += (double) 1.0 / Nsims * firing_rate(t[j], spikes, 0.05);
        };

        // empty the spikes vector for next simulation run
        spikes.clear();
    }

    /* 
       clock_t end = clock();
       double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
       std::cout << "Simulating "
       << Nsims
       << " neurons took "
       << elapsed_secs 
       << " seconds." << std::endl;
    */

    // print out time and rate 
    write_to_stdout(t, rate);
}

int main(int argc, char *argv[])
{
    //// define new neuron with all parameters
    //IF *P = new LIFsig();
    //P->t_0 = 0;
    //P->t_end = 42;
    //P->N = 4000;
    //P->mu = 1.1;
    //P->D = 0.001;
    //P->eps = 0.05;
    //P->f = 0.215;


    IF *P = new LIFsig();
    P->t_0 = 0;
    P->t_end = 5;
    P->N = 5000;
    P->mu = 0.8;
    P->D = 0.1;
    P->eps = 0.1;
    P->f = 1;

    // input routine
    if (argc == 1)
    {
        std::cout << "No arguments passed!" << std::endl;
        exit(0);
    }
    else
    {
        std::string argv1 = argv[1];

        // print curve to file
        if (argv1 == "curveCSV")
        {
            std::vector<double> t;
            std::vector<double> v;
            voltage_curve(P, t, v);

            char fileName[100] = "../data/test.csv";
            write_to_file(fileName, t, v);
        }
        // print curve to standard output
        else if (argv1 == "curveStd")
        {
            std::vector<double> t;
            std::vector<double> v;
            voltage_curve(P, t, v);

            write_to_stdout(t, v);
        }
        // produce firing rate from the neusig lecture
        else if (argv1 == "pif_neusig")
        {
            pif_neusig();
        } else {

            // define vector vor spiketimes, time and firing rate
            std::vector<double> spikes;
            std::vector<double> t;
            std::vector<double> rate;

            // define time scale for firing rate
            int N = 5000;
            double dt = (double)(P->t_end - P->t_0) / N; // time step

            // initial values
            t.push_back(P->t_0);
            rate.push_back(0);

            /* fill time and firing rate vector */
            for (int j = 0; j < N; j++)
            {
                t.push_back(t[j] + dt);
                rate.push_back(0);
            }

            /* loop over simulation */
            int Nsims = 100000;
            for (int i = 0; i < Nsims; i++)
            {
                // get spike times
                spike_times(P, spikes);

                // get firing rate for every time step, weighted with 1/Nsims
                for (int j = 0; j < N; j++)
                {
                    rate[j] += (double)1.0 / Nsims * firing_rate(t[j], spikes, 0.1);
                };

                // empty the spikes vector for next simulation run
                spikes.clear();
            }

            // print out time and rate
            write_to_stdout(t, rate);
        }
    } 

    return 0;
}
