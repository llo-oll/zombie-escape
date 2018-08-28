include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(runTests BoardTests.cpp IntVecTests.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests gameset)


