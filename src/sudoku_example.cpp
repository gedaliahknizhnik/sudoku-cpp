#include <memory>

#include "sudoku_solver_backtracking.hpp"

int main() {
  std::cout << "Sudoku time..."
            << "\n\n";

  auto puzzle{std::make_shared<SudokuBoard>()};
  SudokuSolverBacktracking backtracker{puzzle};

  std::cout << "Starting puzzle: \n" << *puzzle << "\n";
  std::cout << "Solving puzzle...\n";

  bool success{backtracker.solve_puzzle()};

  if (success) {
    std::cout << "Solved the puzzle!\n" << *puzzle << "\n";
  } else {
    std::cout << "No solution found...\n";
  }

  return 0;
}
