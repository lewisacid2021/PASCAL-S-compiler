cmake_minimum_required(VERSION 3.0.0)
project(PascalToC VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(thirdparty)
add_subdirectory(unittest)
add_executable(PascalToC main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
