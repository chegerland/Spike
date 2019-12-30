# add executable
add_executable(CycloHisto
               ${CMAKE_CURRENT_SOURCE_DIR}/cyclohisto.cpp
              )

target_include_directories(CycloHisto PRIVATE ../include)

# link libraries
target_link_libraries(CycloHisto
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
