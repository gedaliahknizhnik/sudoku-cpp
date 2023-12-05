#include <memory>
#include <string>

#include "sudoku_solver_backtracking.hpp"

int main(int argc, char *argv[]) {
  std::string puzzle_file{};

  printf("Sudoku time...\n\n");

  if (argc == 1) {
    printf("You didn't specify a puzzle... :( \n");
    printf("Please pass me a path to the puzzle file!\n");
    return 1;

  } else {
    puzzle_file = argv[1];
  }

  auto puzzle{std::make_shared<SudokuBoard>(puzzle_file)};
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
