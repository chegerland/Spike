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
Spike then parses the file (we followed these [instructions](http://techgate.fr/boost-property-tree/) for the implementation).

An input file always follows the following format

```json
    {
      "Simulation" :
      {
        //PARAMETERS FOR THE SIMULATION
      },
      "Neuron" :
      {
        //PARAMETERS FOR THE NEURON
      }
    }
```

The parameters needed for a specific neuron type are documented in the respective class.
For a more hands on guide to the input files see the [Tutorial](tutorial).
