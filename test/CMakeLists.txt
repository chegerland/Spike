# Executable
add_executable(test_${PROJECT_NAME}
  test_main.cpp
  Models/test_simulation.cpp
  Models/IF/test_PIF.cpp
  Models/IF/test_LIF.cpp
  InputOutput/test_options.cpp
  InputOutput/test_filetools.cpp
  Statistics/test_rate.cpp
  Statistics/test_isi.cpp
)

target_include_directories(test_${PROJECT_NAME} PRIVATE ../include)

target_link_libraries(test_${PROJECT_NAME} PRIVATE
  catch2
  inputoutput
  models
  statistics
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
