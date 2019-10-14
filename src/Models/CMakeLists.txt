# make library
add_library(models SHARED
  Neuron.cpp
  NeuronFactory.cpp
  Simulation.cpp
  IF/IF.cpp
  IF/PIF.cpp
  IF/LIF.cpp
  IF/LIFsig.cpp
  IFadapt/IFadapt.cpp
  IFadapt/PIFadapt.cpp
  IFadapt/LIFadapt.cpp
)

set_target_properties(models PROPERTIES PUBLIC_HEADER include/models.h)
target_include_directories(models PRIVATE src/Models)
