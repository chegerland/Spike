# add directories
add_subdirectory("Models")
add_subdirectory("Statistics")
add_subdirectory("InputOutput")

# add executable
add_executable(${PROJECT_NAME}
               ${CMAKE_CURRENT_SOURCE_DIR}/spike.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/Spike/simulate.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/Spike/ensemble_statistics.cpp
              )

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

# link libraries
target_link_libraries(${PROJECT_NAME}
  inputoutput
  models
  statistics
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

#################################################
