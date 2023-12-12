cmake_minimum_required(VERSION 3.22)

project(
  SudokuCPP
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FLAGS #######################################################################

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# INCLUDES ####################################################################

find_package(Eigen3 REQUIRED)

include(FetchContent)
FetchContent_Declare(
  rapidcsv
  GIT_REPOSITORY https://github.com/d99kris/rapidcsv/
  GIT_TAG f032c52 # v8.8
)

FetchContent_MakeAvailable(rapidcsv)

include_directories(include)

# SUDOKU LIBRARY ##############################################################

add_library(sudoku_lib src/sudoku.cpp include/sudoku.hpp)
target_link_libraries(sudoku_lib Eigen3::Eigen rapidcsv)

add_library(sudoku_solver_backtracking src/sudoku_solver_backtracking.cpp
                                       include/sudoku_solver_backtracking.hpp)
target_link_libraries(sudoku_solver_backtracking sudoku_lib)

# EXAMPLES ####################################################################

add_executable(solve src/sudoku_example.cpp)
target_link_libraries(solve sudoku_lib sudoku_solver_backtracking)
