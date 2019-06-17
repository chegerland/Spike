add_subdirectory("Models")

# Executable
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/spike.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC models)
