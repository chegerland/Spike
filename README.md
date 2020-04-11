[![pipeline status](https://git.physik.hu-berlin.de/cheg/master/spike/badges/master/pipeline.svg)](https://git.physik.hu-berlin.de/cheg/master/spike/commits/master)

# Spike
Spike is a small numerical toolset that can simulate single neurons and evaluate the resulting spike trains statistically by calculation all sorts of quantities like the firing rate etc.
It is build as a library with which you can write your own scripts, it comes, however, with some useful executables ready to use.

### Dependencies
* [Catch2](https://github.com/catchorg/Catch2): unit testing
* [doxygen](http://doxygen.nl/): API documentation
* [boost](https://www.boost.org/): json file parser, program options and logging
* [progress bar](https://github.com/prakhar1989/progress-cpp)

### Installation & Build
To install Spike, clone the repository by typing

```
git clone https://git.physik.hu-berlin.de/cheg/master/Spike.git
```

then create a build directory and build the project using cmake

```
mkdir -p build/ && cd build
cmake .. &&  make
```

### First Calculation
One of the out-of-the-box executables is `firing_rate`.
Given a `.json` input file, this program calculates the firing rate of the neuron.
An example file looks like this:
```json
```

## Testing
We try to follow a [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development) style.
To build all tests type

```
make tests_Spike
```

and run them with

```
./tests_Spike
```

## Documentation
Notes are written in `.md` files in the `docs/` directory.
Classes and functions are documented in the according `.h` files and an API documentation can be generated from them using (inside the `docs/doxygen` directory)
```
doxygen Doxyfile
```

Details on the implementation are written in `.cpp` files.


## Development
The master branch should at all times contain a working copy of Spike.
New features are added via [feature branches](https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow).
The master is locked, the only way to get code into the master is by merging feature branches, which triggers the CI pipieline to make sure the master is building and passes all tests.


## Guidelines
We mostly follow the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
Some important conventions we follow are:
* Use a `.cpp` suffix for code files and `.h` for interface files.
* Use include guards for all `.h` files.
* Document code in the `.h` files.
* Only declare functions in headers, write the actual code in the respective `.cpp` file.


## Authors
Christoph Egerland [@egerlanc](https://git.physik.hu-berlin.de/egerlanc)
