[![build](https://github.com/chegerland/Spike/actions/workflows/build.yml/badge.svg)](https://github.com/chegerland/Spike/actions/workflows/build.yml)
[![docs](https://github.com/chegerland/Spike/actions/workflows/docs.yml/badge.svg)](https://github.com/chegerland/Spike/actions/workflows/docs.yml)


# Spike
Spike is a small numerical toolset that can simulate single neurons and evaluate the resulting spike trains statistically by calculation all sorts of quantities like the firing rate etc.
It is build as a library with which you can write your own scripts, it comes, however, with some useful executables ready to use.

### Dependencies
* [Catch2](https://github.com/catchorg/Catch2): unit testing
* [doxygen](http://doxygen.nl/): API documentation
* [boost](https://www.boost.org/): json file parser, program options and logging

### Installation & Build
To install Spike, clone the repository by typing

```
git clone https://github.com/chegerland/Spike.git
```

then create a build directory and build the project using cmake (the `j` flag tells make to execute in parallel)

```
mkdir -p build/ && cd build
cmake .. &&  make -j 4
```

## Documentation
Classes and functions are documented in the according `.h` files and an API documentation can be generated from them using (inside the `docs/doxygen` directory)
```
doxygen Doxyfile
```
which can also be viewed here: [chegerland.github.io/Spike](https://chegerland.github.io/Spike/index.html)

Details on the implementation are written in `.cpp` files.


## Development
The main branch should at all times contain a working copy of Spike.
New features should be added via [feature branches](https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow).
For now, since I am the only one working on this project, I am directly using the the main branch.


## Guidelines
We mostly follow the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
Some important conventions we follow are:
* Use a `.cpp` suffix for code files and `.h` for interface files.
* Use include guards for all `.h` files.
* Document code in the `.h` files.
* Only declare functions in headers, write the actual code in the respective `.cpp` file.


## Authors
Christoph Egerland [@egerlanc](https://git.physik.hu-berlin.de/egerlanc)
