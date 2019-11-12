# add executable
add_executable(Stumpf
               ${CMAKE_CURRENT_SOURCE_DIR}/stumpf.cpp
              )

target_include_directories(Stumpf PRIVATE ../include)
