#include <memory>
#include <string>

#include "sudoku_solver_backtracking.hpp"

/**
 * @brief Run the puzzle solver.
 */
int main(int argc, char *argv[]) {
  std::string puzzle_file{};

  // Check for a passed in puzzle file
  if (argc == 1) {
    printf("You didn't specify a puzzle... :( \n");
    printf("Please pass me a path to the puzzle file!\n");
    printf("Usage:\n");
    printf("\t solve [path to puzzle csv]\n");
    return 1;

  } else {
    puzzle_file = argv[1];
  }

  printf("Sudoku time...\n");
  printf("==============\n");

  auto puzzle{std::make_shared<sudoku::SudokuBoard>(puzzle_file)};
  sudoku::SudokuSolverBacktracking backtracker{puzzle};

  printf("Starting puzzle:\n");
  std::cout << *puzzle << "\n";
  printf("Solving puzzle...\n");

  bool success{backtracker.solve_puzzle()};

  if (success) {
    std::cout << "Solved the puzzle!\n" << *puzzle << "\n";
  } else {
    std::cout << "No solution found...\n";
  }

  return 0;
}
