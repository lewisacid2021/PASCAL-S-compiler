cmake_minimum_required(VERSION 3.0.0)
project(PascalToC VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

if(FLEX_FOUND AND BISON_FOUND)
  message(STATUS "FLEX AND BISON FOUND")
  BISON_TARGET(Parser ${CMAKE_BINARY_DIR}/../scripts/parser.y  ${CMAKE_BINARY_DIR}/../scripts/parser.tab.cpp  DEFINES_FILE  ${CMAKE_BINARY_DIR}/../include/parser.tab.h COMPILE_FLAGS "-t")
  FLEX_TARGET(Lexer  ${CMAKE_BINARY_DIR}/../scripts/lex.l  ${CMAKE_BINARY_DIR}/../scripts/lex.yy.cpp)
  ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/scripts)
add_subdirectory(thirdparty)
add_subdirectory(unittest)

file(GLOB SRC_FILES src/*.cpp)
message(STATUS "SRC_FILES: ${SRC_FILES}")

add_executable(pascc 
  main.cpp
  ${SRC_FILES}
  ${PROJECT_SOURCE_DIR}/scripts/parser.tab.cpp
  ${PROJECT_SOURCE_DIR}/scripts/lex.yy.cpp
  )

  set_target_properties(pascc PROPERTIES LINK_SEARCH_START_STATIC ON)
  set_target_properties(pascc PROPERTIES LINK_SEARCH_END_STATIC ON)
  
  target_link_options(pascc PRIVATE -static-libgcc -static-libstdc++ -static)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
