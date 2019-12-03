# add executable
add_executable(Cyclo
    ${CMAKE_CURRENT_SOURCE_DIR}/cyclo.cpp
              )

target_include_directories(Cyclo PRIVATE ../include)

# link libraries
target_link_libraries(Cyclo
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
