cmake_minimum_required(VERSION 3.0.0)
project(PascalToC VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# 设置 Flex 和 Bison 的目录
set(SCRIPTS_DIR ${PROJECT_SOURCE_DIR}/scripts)

# 使用 Flex 和 Bison 生成词法和语法分析器
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

flex_target(Lexer ${SCRIPTS_DIR}/lex.l ${SCRIPTS_DIR}/lex.yy.c)
bison_target(Parser ${SCRIPTS_DIR}/parser.y ${SCRIPTS_DIR}/y.tab.c)

add_flex_bison_dependency(Lexer Parser)

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
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
