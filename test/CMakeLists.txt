# add sources to test
set(test_sources
        test_main.cpp
        IF/test_PIF.cpp
        IF/test_LIF.cpp
        Signal/test_WhiteNoiseSignal.cpp
        Signal/test_TwoCosineSignal.cpp
        Signal/test_StepSignal.cpp
        Signal/test_CosineSignal.cpp
        SpikeTrain/test_SpikeTrain.cpp
        TimeFrame/test_TimeFrame.cpp
        )

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
