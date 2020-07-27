# add executable
add_executable(firing_rate_mpi
        ${CMAKE_CURRENT_SOURCE_DIR}/firing_rate_mpi.cpp
        )

target_include_directories(firing_rate_mpi PRIVATE ../include)

# link libraries
target_link_libraries(firing_rate_mpi
        spike
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        MPI::MPI_CXX
        OpenMP::OpenMP_CXX
        )
