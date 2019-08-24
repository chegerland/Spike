# make library
add_library(models SHARED
            Neuron.cpp
            IF/IF.cpp
            IF/PIF.cpp
            IF/LIF.cpp
            IF/LIFsig.cpp
           )

set_target_properties(models PROPERTIES PUBLIC_HEADER include/models.h)
target_include_directories(models PRIVATE src/Models)
