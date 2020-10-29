# add spike library
set(spike_sources
        FFT/fft.cpp
        Integration/Integrations.cpp
        Neuron/NeuronFactory.cpp
        Neuron/IF.cpp
        Neuron/IFAC.cpp
        Signal/CosineSignal.cpp
        Signal/Signal.cpp
        Signal/SignalFactory.cpp
        Signal/StepSignal.cpp
        Signal/TwoCosineSignal.cpp
        Signal/WhiteNoiseSignal.cpp
        Simulation/SusceptibilitySimulation.cpp
        Simulation/SusceptibilitySimulationLinNonlin.cpp
        Simulation/SusceptibilitySimulationNonlin.cpp
        Simulation/FiringRateSimulation.cpp
        SpikeTrain/SpikeTrain.cpp
        Statistics/statistics.cpp
        TimeFrame/TimeFrame.cpp
        )
add_library(spike SHARED ${spike_sources})
target_link_libraries(spike
        ${GSL_LIBRARY}
        ${GSL_CBLAS_LIBRARY}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${FFTW_LIBRARIES}
        )
set_target_properties(spike PROPERTIES PUBLIC_HEADER Spike.h)
