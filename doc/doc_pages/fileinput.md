# File input and API

## Program options
Spike is envoked in the command line and uses [boost program options](https://www.boost.org/doc/libs/1_71_0/doc/html/program_options/tutorial.html) for its API.
We know that there exists a simple .INI-like file parser within *boost_program_options*, but we prefer `.json` files.

## Input File
We try to give the data to the program in the form of `.json` files and use the boost library to parse them.
For the implementation we followed this [tutorial](http://techgate.fr/boost-property-tree/).
