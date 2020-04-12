# add sources to test
file(GLOB_RECURSE test_sources ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

# Executable
add_executable(test_${PROJECT_NAME}
        ${test_sources}
        )

target_include_directories(test_${PROJECT_NAME} PRIVATE ../include)

target_link_libraries(test_${PROJECT_NAME} PUBLIC
        catch2
        spike
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        OpenMP::OpenMP_CXX
        )
