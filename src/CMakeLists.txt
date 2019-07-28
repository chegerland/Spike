# add directories
add_subdirectory("Neuron")
add_subdirectory("IO")
add_subdirectory("Statistics")

# add executable
add_executable(${PROJECT_NAME} 
               ${CMAKE_CURRENT_SOURCE_DIR}/spike.cpp
              )

# link libraries
target_link_libraries(${PROJECT_NAME} 
                      neuron
                      io
                      statistics
                     )
