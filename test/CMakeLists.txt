# Executable
add_executable(test_${PROJECT_NAME}
               ${CMAKE_CURRENT_SOURCE_DIR}/tests_main.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/tests_neuron.cpp
              )

target_link_libraries(test_${PROJECT_NAME} PRIVATE catch2
                                                  neuron
                                                  )
