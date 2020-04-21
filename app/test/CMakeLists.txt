# add executable
add_executable(test
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
        )

target_include_directories(test PRIVATE ../include)

# link libraries
target_link_libraries(test PUBLIC
        spike
        )
