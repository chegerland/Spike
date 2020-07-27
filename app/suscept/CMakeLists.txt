# add executable
add_executable(suscept
        ${CMAKE_CURRENT_SOURCE_DIR}/suscept.cpp
        )

target_include_directories(suscept PRIVATE ../include)

# link libraries
target_link_libraries(suscept PUBLIC
        OpenMP::OpenMP_CXX
        spike
        )
