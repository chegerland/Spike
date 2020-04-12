# add executable
add_executable(firing_rate
        ${CMAKE_CURRENT_SOURCE_DIR}/firing_rate.cpp
        )

target_include_directories(firing_rate PRIVATE ../include)

# link libraries
target_link_libraries(firing_rate
        OpenMP::OpenMP_CXX
        spike
        )
