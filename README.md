[![pipeline status](https://git.physik.hu-berlin.de/cheg/master/spike/badges/master/pipeline.svg)](https://git.physik.hu-berlin.de/cheg/master/spike/commits/master)

# Spike

Spike is a small numerical toolset that can simulate single neurons and evaluate the resulting spike trains statistically by calculation all sorts of quantities like the firing rate etc.

## Getting Started
These instructions will help you set up Spike and run your first calculation.

### Dependencies

### Installation & Build
To install Spike, clone the repository by typing

  $ git clone https://git.physik.hu-berlin.de/cheg/master/Spike.git

then create a build directory and build the project using cmake

  $ mkdir -p build/ && cd build
  $ cmake ..
  $ make Spike

### First Calculation
Run your first calculation, by giving Spike the following input file called `tutorial.json`:


## Testing
We use [Catch2]() to unit test our code.

To build all tests type

  $ make tests_Spike

and run them with

  $ ./tests_Spike


## Documentation
The documentation is build using [doxygen]().
Notes are written in `.md` files in the `docs/doc_pages/` directory.

## Authors
Christoph Egerland [@egerlanc](https://git.physik.hu-berlin.de/egerlanc)
