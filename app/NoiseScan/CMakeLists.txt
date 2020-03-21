# add executable
add_executable(NoiseScan
        ${CMAKE_CURRENT_SOURCE_DIR}/noise.cpp
              )

target_include_directories(NoiseScan PRIVATE ../include)

# link libraries
target_link_libraries(NoiseScan
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
