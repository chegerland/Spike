# add executable
add_executable(FiringRate
        ${CMAKE_CURRENT_SOURCE_DIR}/firing_rate.cpp
        )

target_include_directories(FiringRate PRIVATE ../include)

# link libraries
target_link_libraries(FiringRate
        spike
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
