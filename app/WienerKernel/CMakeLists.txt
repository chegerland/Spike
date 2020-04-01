# add executable
add_executable(WienerKernel
        ${CMAKE_CURRENT_SOURCE_DIR}/wiener.cpp
        )

target_include_directories(WienerKernel PRIVATE ../include)

# link libraries
target_link_libraries(WienerKernel
        spike
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
