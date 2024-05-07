cmake_minimum_required(VERSION 3.0.0)
project(PascalToC VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

find_package(FLEX)
find_package(BISON)

if(FLEX_FOUND AND BISON_FOUND)
  BISON_TARGET(Parser ${PROJECT_SOURCE_DIR}/scripts/parser.y  ${PROJECT_SOURCE_DIR}/scripts/parser.tab.cpp  DEFINES_FILE  ${PROJECT_SOURCE_DIR}/include/parser.tab.h COMPILE_FLAGS "-t")
  FLEX_TARGET(Lexer  ${PROJECT_SOURCE_DIR}/scripts/lex.l  ${PROJECT_SOURCE_DIR}/scripts/lex.yy.cpp)
  ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)
endif()

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/scripts)
add_subdirectory(thirdparty)
add_subdirectory(unittest)

file(GLOB SRC_FILES src/*.cpp)
message(STATUS "SRC_FILES: ${SRC_FILES}")

file(GLOB SCRIPTS_FILES src/*.c)
message(STATUS "SCRIPTS_FILES: ${SCRIPTS_FILES}")

add_executable(PascalToC main.cpp ${PROJECT_SOURCE_DIR}/src/visitor.cpp ${SCRIPTS_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
