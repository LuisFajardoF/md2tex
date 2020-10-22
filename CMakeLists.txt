cmake_minimum_required (VERSION 3.8)
project (md2tex)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(RE2C REQUIRED)

# Run re2c to generate the lexer
add_custom_command (
  OUTPUT lexer.cpp
  COMMAND ${RE2C} -o lexer.cpp ${PROJECT_SOURCE_DIR}/lexer.re --utf-8
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/lexer.re
)

# Run bison to generate the parser
add_custom_command (
    OUTPUT parser.cpp parser.h
    COMMAND bison -o parser.cpp --defines=parser.h ${PROJECT_SOURCE_DIR}/parser.y
    MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/parser.y
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})
  
add_executable(${PROJECT_NAME}  lexer.cpp
                            parser.cpp
                            main.cpp)

