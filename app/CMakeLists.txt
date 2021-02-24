# suscept executable
add_executable(spike_suscept
        ${CMAKE_CURRENT_SOURCE_DIR}/spike_suscept.cpp
        )
target_link_libraries(spike_suscept PUBLIC
        MPI::MPI_CXX
        spike
        )

# suscept_lin_novikov executable
add_executable(spike_suscept_lin_novikov
        ${CMAKE_CURRENT_SOURCE_DIR}/spike_suscept_lin_novikov.cpp
        )
target_link_libraries(spike_suscept_lin_novikov PUBLIC
        MPI::MPI_CXX
        spike
        )

# suscept nonlin executable
add_executable(spike_suscept_nonlin
        ${CMAKE_CURRENT_SOURCE_DIR}/spike_suscept_nonlin.cpp
        )
target_link_libraries(spike_suscept_nonlin PUBLIC
        MPI::MPI_CXX
        spike
        )

# firing rate executable
add_executable(spike_firing_rate
        ${CMAKE_CURRENT_SOURCE_DIR}/spike_firing_rate.cpp
        )
target_link_libraries(spike_firing_rate PUBLIC
        MPI::MPI_CXX
        spike
        )

# test executable
add_executable(spike_test spike_test.cpp)
target_link_libraries(spike_test PUBLIC spike)

# r0_mu executable
add_executable(spike_r0_mu spike_r0_mu.cpp)
target_link_libraries(spike_r0_mu PUBLIC spike)

# trajectory executable
add_executable(spike_trajectory spike_trajectory.cpp)
target_link_libraries(spike_trajectory PUBLIC spike)
