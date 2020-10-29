# suscept executable
add_executable(spike_suscept
        ${CMAKE_CURRENT_SOURCE_DIR}/spike_suscept.cpp
        )
target_link_libraries(spike_suscept PUBLIC
        MPI::MPI_CXX
        OpenMP::OpenMP_CXX
        spike
        )

# suscept nonlin executable
add_executable(spike_suscept_nonlin
        ${CMAKE_CURRENT_SOURCE_DIR}/spike_suscept_nonlin.cpp
        )
target_link_libraries(spike_suscept_nonlin PUBLIC
        MPI::MPI_CXX
        OpenMP::OpenMP_CXX
        spike
        )

# firing rate executable
add_executable(spike_firing_rate
        ${CMAKE_CURRENT_SOURCE_DIR}/spike_firing_rate.cpp
        )
target_link_libraries(spike_firing_rate PUBLIC
        MPI::MPI_CXX
        OpenMP::OpenMP_CXX
        spike
        )

# test executable
add_executable(spike_test spike_test.cpp)
target_link_libraries(spike_test PUBLIC spike)

