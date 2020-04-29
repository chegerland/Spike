# add spike library
file(GLOB_RECURSE spike_sources ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
set(spike_sources
        FFT/fft.cpp
        Neuron/NeuronFactory.cpp
        Neuron/IF/IF.cpp
        Neuron/IF/PIF.cpp
        Neuron/IF/LIF.cpp
        Neuron/IFAC/IFAC.cpp
        Neuron/IFAC/PIFAC.cpp
        Neuron/IFAC/LIFAC.cpp
        Signal/CosineSignal.cpp
        Signal/Signal.cpp
        Signal/SignalFactory.cpp
        Signal/StepSignal.cpp
        Signal/TwoCosineSignal.cpp
        Signal/WhiteNoiseSignal.cpp
        SpikeTrain/SpikeTrain.cpp
        Statistics/statistics.cpp
        Susceptibility/Susceptibility.cpp
        TimeFrame/TimeFrame.cpp
        )
add_library(spike SHARED ${spike_sources})
target_link_libraries(spike
        OpenMP::OpenMP_CXX
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${BLAS_LIBRARIES}
        ${LAPACK_LIBRARIES}
        )
set_target_properties(spike PROPERTIES PUBLIC_HEADER include/Spike.h)
