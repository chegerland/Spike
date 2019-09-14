# Tutorial {#tutorial}

We expect you to have Spike readily installed.
In this small tutorial we will set up our first simulation and even retrieve some statistics from it.

## Input file
The input file for our simulation is `data/tutorial.json` and looks like this

~~~~~~~~~~~~~~~~~~~~~~~~{.java}
    {
      "Simulation" :
      {
        "t_0" : 0,
        "t_end" : 10,
        "dt" : 1e-3,
        "N" : 10000
      },
      "Neuron" :
      {
        "type" : "LIF",
        "mu" : 1.0,
        "D" : 0.2
      }
    }
~~~~~~~~~~~~~~~~~~~~~~~~

As you can see we will simulate a leaky integrate and fire neuron (LIF) with a drift coefficient of 1 and a diffusion coefficient of 0.2.
The time frame and time step is specified in the Simulation bracket.
There you can also see that we will repeat this simulation 10.000 times.

## Your first simulation
You can run the simulation by typing

    Spike/bin $ ./Spike --mode 0 --file ../data/tutorial.json

This produces in output file called `tutorial.out` inside the data folder.
Have a look at it.
You can see that each row contains the times where the neuron has spiked and there are 10.000 rows, just as many as we wanted.

## Statistics
To obtain statistics from the above simulation type

    Spike/bin $ ./Spike --mode 1 --file ../data/tutorial.json --isi

This requires, that `tutorial.out` exists!
Spike now calculates the interspike intervals and outputs a file called `tutorial_isi.out` which contains the long list of interspike intervals.
Plot them as a histogram.
Does it look like you expected?
