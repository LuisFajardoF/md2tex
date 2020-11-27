cmake_minimum_required (VERSION 3.8)
project (md2tex)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(TREECC REQUIRED)

# Run flex to generate the lexer
add_custom_command (
  OUTPUT lexer.cpp
  COMMAND flex -o lexer.cpp ${PROJECT_SOURCE_DIR}/lexer.l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/lexer.l
)

# Run bison to generate the parser
add_custom_command (
    OUTPUT parser.cpp parser.h
    COMMAND bison -o parser.cpp -rall --defines=parser.h ${PROJECT_SOURCE_DIR}/parser.y
    MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/parser.y
)

# Run treecc to generate the ast
add_custom_command(
  OUTPUT ast.cpp
  COMMAND ${TREECC} -o ast.cpp -h ast.h ${PROJECT_SOURCE_DIR}/ast.tc
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/ast.tc
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
  
add_executable(${PROJECT_NAME}  ast.cpp
                            parser.cpp
                            lexer.cpp
                            main.cpp)

