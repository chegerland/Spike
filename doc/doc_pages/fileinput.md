# File input and API

## Command line options
Spike is envoked in the command line and uses [boost program options](https://www.boost.org/doc/libs/1_71_0/doc/html/program_options/tutorial.html) for its API.
The possible options are:

|                 |                                                                        |
| --------------- | ---------------------------------------------------------------------- |
| `--mode` arg    | Select the mode (0 for simulation, 1 for evaluation)                   |
| `--file` arg    | Path to input file                                                     |
| `--rate` arg    | Calculate firing rate (in evaluation mode only!) with time bin arg     |
| `--isi`         | Calculate interspike intervals (in evaluation mode only!)              |
| `-h [ --help ]` | Print this help message                                                |


## Input File
Parameters are given to spike in the form of `.json` files.
Spike then parses the file (we followed this [tutorial](http://techgate.fr/boost-property-tree/) for the implementation).

An input file always follows the following format

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

As you can see there are parameters concerning the simulation and parameters concerning the neuron.
