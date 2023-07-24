cmake_minimum_required(VERSION 3.22)

project(
    SudokuCPP
    VERSION 1.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Find packages go here.

# You should usually split this into folders, but this is a simple example

# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system
# add_library(sudoku_lib sudoku.cpp)

# Link each target with other targets or add options, etc.

# Adding something we can run - Output name matches target name
# add_executable(sudoku sudoku_example.cpp)
add_executable(sudoku sudoku.cpp)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
# target_link_libraries(sudoku PRIVATE sudoku_lib)