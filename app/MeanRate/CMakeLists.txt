# add executable
add_executable(Mean
               ${CMAKE_CURRENT_SOURCE_DIR}/mean.cpp
              )

target_include_directories(Mean PRIVATE ../include)

# link libraries
target_link_libraries(Mean
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
