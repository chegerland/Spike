# make library
add_library(simulation SHARED
  Simulation.cpp
)

set_target_properties(simulation PROPERTIES PUBLIC_HEADER include/simulation.h)
target_include_directories(simulation PRIVATE src/Simulation)
