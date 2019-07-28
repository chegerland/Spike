# Spike {#mainpage}

Spike is a small numerical toolset that can simulate single neurons and calculate statistics from these simulations.


## Installation
Clone the git repository to obtain the code

    git clone git@git.physik.hu-berlin.de:cheg/master/spike.git

and type the following commands inside the `build` directory to build the code

    cmake ..
    make


## Getting started
After a succesfull installation you will find a binary called `Spike` inside the `bin` directory.
Spike has two modes: 1) simulation mode and 2) (statistical) evaluation mode.
In the **simulation mode** Spike needs an input file `my_simulation.in` with parameters defining the simulation and produces an according `my_simulation.out` file containing the times when the neuron has spiked.
In the **evaluation mode** you can give Spike an `.out` file and calculate the firing rate, ISI density and much more.

API DOCUMENTATION

## Documentation
To build the documentation go inside the `doc` directory and run

    doxygen Doxyfile.in

Open `doc/doxygen/html/index.html/` inside a browser to view the documentation.

## Testing
After a succesfull installation you will also find a binary called `test_Spike` inside the `bin` directory.
Run it with 

    ./test_Spike

to unit test the code.


Notes:
- i think it makes perfect sense for this code, that the neuron model classes only contain public members, because i actually want to read and write from or to them. capsulation would just make this more complicated
