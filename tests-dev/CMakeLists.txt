cmake_minimum_required (VERSION 3.8)
project (genLatex)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
  
add_executable(${PROJECT_NAME} tests/test_cases.cpp)

