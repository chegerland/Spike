# add executable
add_executable(RateOnePeriod
               ${CMAKE_CURRENT_SOURCE_DIR}/rateoneperiod.cpp
              )

target_include_directories(RateOnePeriod PRIVATE ../include)

# link libraries
target_link_libraries(RateOnePeriod
  spike
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
