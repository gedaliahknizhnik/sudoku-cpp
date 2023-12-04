cmake_minimum_required(VERSION 3.22)

project(
    SudokuCPP
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## FLAGS #######################################################################

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

## INCLUDES ####################################################################

find_package(Eigen3 REQUIRED)

include_directories(include)

## SUDOKU LIBRARY ##############################################################

add_library(sudoku_lib src/sudoku.cpp include/sudoku.hpp)
target_link_libraries(sudoku_lib Eigen3::Eigen)

## EXAMPLES ####################################################################

add_executable(example_sudoku src/sudoku_example.cpp)
target_link_libraries(example_sudoku sudoku_lib)
