# make library
set(neuronSource neuron.h neuron.cpp)
add_library(neuron SHARED ${neuronSource})
