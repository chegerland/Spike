# add spike library
file(GLOB_RECURSE spike_sources ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
add_library(spike SHARED ${spike_sources})
target_link_libraries(spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
set_target_properties(spike PROPERTIES PUBLIC_HEADER include/Spike.h)
