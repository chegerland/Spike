# add executable
add_executable(${PROJECT_NAME}
               ${CMAKE_CURRENT_SOURCE_DIR}/spike.cpp
              )

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

# link libraries
target_link_libraries(${PROJECT_NAME}
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
