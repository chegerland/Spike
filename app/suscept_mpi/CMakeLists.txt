# add executable
add_executable(suscept_mpi
        ${CMAKE_CURRENT_SOURCE_DIR}/suscept_mpi.cpp
        )

target_include_directories(suscept_mpi PRIVATE ../include)

# link libraries
target_link_libraries(suscept_mpi PUBLIC
        MPI::MPI_CXX
        OpenMP::OpenMP_CXX
        spike
        )
