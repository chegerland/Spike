# Executable
add_executable(test_${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/tests_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Models/tests_neuron.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Statistics/tests_statistics.cpp
)

target_include_directories(test_${PROJECT_NAME} PRIVATE ../include)

target_link_libraries(test_${PROJECT_NAME} PRIVATE catch2
                                                  models
                                                  simulation
                                                  statistics
                                                  )
