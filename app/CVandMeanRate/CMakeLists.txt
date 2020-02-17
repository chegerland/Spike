# add executable
add_executable(CVrate
               ${CMAKE_CURRENT_SOURCE_DIR}/cvrate.cpp
              )

target_include_directories(CVrate PRIVATE ../include)

# link libraries
target_link_libraries(CVrate
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
