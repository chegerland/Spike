# add directories
add_subdirectory("Models")
add_subdirectory("Statistics")
add_subdirectory("Simulation")
add_subdirectory("InputOutput")

# add executable
add_executable(${PROJECT_NAME}
               ${CMAKE_CURRENT_SOURCE_DIR}/spike.cpp
              )

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

# link libraries
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} boost_program_options)
target_link_libraries(${PROJECT_NAME} boost_filesystem)
target_link_libraries(${PROJECT_NAME} boost_system)
target_link_libraries(${PROJECT_NAME}
  inputoutput
  simulation
  models
  statistics
)
