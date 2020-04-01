# add executable
add_executable(SusceptibilityScanNew
        ${CMAKE_CURRENT_SOURCE_DIR}/suscept_scan.cpp
        )

target_include_directories(SusceptibilityScanNew PRIVATE ../include)

# link libraries
target_link_libraries(SusceptibilityScanNew
        spike
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
