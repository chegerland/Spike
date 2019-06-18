# add directories
add_subdirectory("Models")
add_subdirectory("InputOutput")

# add executable
add_executable(${PROJECT_NAME} 
               ${CMAKE_CURRENT_SOURCE_DIR}/spike.cpp
              )

# link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC models)
target_link_libraries(${PROJECT_NAME} PUBLIC inputoutput)
