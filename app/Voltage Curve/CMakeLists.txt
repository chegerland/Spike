# add executable
add_executable(Curves
               ${CMAKE_CURRENT_SOURCE_DIR}/curve.cpp
              )

target_include_directories(Curves PRIVATE ../include)

# link libraries
target_link_libraries(Curves
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
