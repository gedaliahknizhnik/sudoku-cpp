cmake_minimum_required(VERSION 3.22)

project(
    SudokuCPP
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find packages go here.
find_package(Eigen3)

# You should usually split this into folders, but this is a simple example
include_directories(include)

# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system
add_library(sudoku_lib SHARED sudoku.cpp include/sudoku.hpp)
target_link_libraries(sudoku_lib Eigen3::Eigen)

## EXAMPLES ####################################################################

add_executable(example_sudoku src/sudoku_example.cpp)
target_link_libraries(sudoku sudoku_lib)
