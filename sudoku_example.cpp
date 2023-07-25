#include "sudoku.hpp"

int main() {
    std::cout << "Sudoku time..."
              << "\n\n";

    SudokuBoard s{};

    std::cout << "Starting puzzle: \n"
              << s << "\n";
    std::cout << "Solving puzzle...\n";

    bool success{s.solvePuzzle()};

    if (success) {
        std::cout << "Solved the puzzle!\n"
                  << s << "\n";
    } else {
        std::cout << "No solution found...\n";
    }

    return 0;
}