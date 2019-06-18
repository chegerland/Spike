# Executable
add_executable(${PROJECT_NAME}test 
               ${CMAKE_CURRENT_SOURCE_DIR}/tests-main.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/tests-models.cpp
              )
target_link_libraries(${PROJECT_NAME}test PUBLIC models)
