# Code structure

The code is organized as follows:
In the `.src` directory are the source files for Spike.
There you will find folders which contain the libraries and a single `.cpp` file called `spike.cpp`, which contains the main function.

The only folder that does not contain a library is called `Spike/`, it contains the actual *app*.

**Design note**: Libraries should be written such that they are independent from one another!

## Libraries

1) InputOutput
The InputOutput library contains functions handling the command line options.

2) Models
The Models library contains the class definition of a neuron (for more information see ...), the simulation as well as a bunch of neuron models which are organized in further subfolders.
For now there is just one subfolder containing the class of integrate-and-fire neurons.

3) Statistics
The Statistics library contains functions which analyze the output files of the simulation such as the firing rate, ...
