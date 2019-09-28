# Project structure

## Folder structure

The project is organized as follows:

```bash
    Spike/
    ├── bin
    ├── build
    ├── data
    ├── doc
    ├── include
    ├── lib
    ├── src
    └── test
```

The directory contains ...

- `bin/`: the executables (binary files)
- `build/`: build files produced by cmake
- `data/`: various data files for the tests, tutorials and other applications
- `doc/`: the documentation
- `include/`: library headers
- `src/`: source files for libraries and the *app* spike
- `test/`: unit tests

## Libraries
The project contains several libraries, fulfilling different purposes.
**Design note**: Libraries should be written such that they are independent from one another!

The libraries are

**InputOutput**

The InputOutput library contains:

* functions handling the command line options
* functions handling file input and output

**Models**

The Models library contains the class definition of a Neuron, the Simulation as well as a bunch of neuron models which are organized in further subfolders.
For now there is just one subfolder containing the class of integrate-and-fire neurons.

**Statistics**

The Statistics library contains functions which analyze the output files of the simulation such as the firing rate, isi, ...

## Spike
The actual executable is called spike, the code for which is found in `src/spike.cpp` and `src/Spike/`.
