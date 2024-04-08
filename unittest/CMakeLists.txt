include(GoogleTest)

file(GLOB UNITTEST_SOURCES "*/*_gtest.cpp")
message(STATUS "Found unit tests: ${UNITTEST_SOURCES}")

foreach(UnitTestSource ${UNITTEST_SOURCES})
    get_filename_component(UnitTestName ${UnitTestSource} NAME_WE)
    add_executable(${UnitTestName} ${UnitTestSource})
    message(STATUS "Adding unit test: ${UnitTestName}")
    target_link_libraries(${UnitTestName} gtest_main)
    # target_link_libraries(${UnitTestName} ${PROJECT_NAME})
    gtest_discover_tests(${UnitTestName})
endforeach()

file(GLOB BENCHMARK_SOURCES "*/*_benchmark.cpp")
message(STATUS "Found benchmark sources: ${BENCHMARK_SOURCES}")

foreach(BenchmarkSource ${BENCHMARK_SOURCES})
    get_filename_component(BenchmarkName ${BenchmarkSource} NAME_WE)
    add_executable(${BenchmarkName} ${BenchmarkSource})
    message(STATUS "Adding benchmark: ${BenchmarkName}")
    target_link_libraries(${BenchmarkName} benchmark::benchmark)
endforeach()