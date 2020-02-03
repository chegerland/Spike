# add executable
add_executable(CV
               ${CMAKE_CURRENT_SOURCE_DIR}/cv.cpp
              )

target_include_directories(CV PRIVATE ../include)

# link libraries
target_link_libraries(CV
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
