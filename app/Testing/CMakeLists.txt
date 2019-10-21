# add executable
add_executable(Testing
               ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
              )

target_include_directories(Testing PRIVATE ../include)

# link libraries
target_link_libraries(Testing
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
