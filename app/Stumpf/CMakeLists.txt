# add executable
add_executable(Stumpf
               ${CMAKE_CURRENT_SOURCE_DIR}/stumpf.cpp
              )

target_include_directories(Stumpf PRIVATE ../include)

# link libraries
target_link_libraries(Stumpf
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
