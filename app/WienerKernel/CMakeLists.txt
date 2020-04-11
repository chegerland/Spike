# add executable
add_executable(Wiener
        ${CMAKE_CURRENT_SOURCE_DIR}/wiener.cpp
        )

target_include_directories(Wiener PRIVATE ../include)

# link libraries
target_link_libraries(Wiener
        spike
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
