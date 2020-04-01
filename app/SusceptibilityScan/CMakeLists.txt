# add executable
add_executable(SusceptibilityScan
        ${CMAKE_CURRENT_SOURCE_DIR}/suscept_scan.cpp
        )

target_include_directories(SusceptibilityScan PRIVATE ../include)

# link libraries
target_link_libraries(SusceptibilityScan
        spike
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
