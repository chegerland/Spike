file(GLOB_RECURSE test_sources ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

# Executable
add_executable(test_${PROJECT_NAME} ${test_sources})

target_link_libraries(test_${PROJECT_NAME} PRIVATE catch2
                                                  neuron
                                                  io
                                                  statistics
                                                  )
