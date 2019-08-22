# add directories
add_subdirectory("Models")
add_subdirectory("Statistics")
add_subdirectory("Simulation")

# add executable
add_executable(${PROJECT_NAME}
               ${CMAKE_CURRENT_SOURCE_DIR}/spike.cpp
              )

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

# link libraries
target_link_libraries(${PROJECT_NAME}
  simulation
  models
  statistics
)
