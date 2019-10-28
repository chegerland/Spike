# add executable
add_executable(Susc
               ${CMAKE_CURRENT_SOURCE_DIR}/susc.cpp
              )

target_include_directories(Susc PRIVATE ../include)

# link libraries
target_link_libraries(Susc
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
