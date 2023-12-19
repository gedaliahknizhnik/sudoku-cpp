#include "sudoku_solver_backtracking.hpp"

#include <memory>

namespace sudoku {

SudokuSolverBacktracking::SudokuSolverBacktracking(
    std::shared_ptr<SudokuBoard> board)
    : _board{board} {}

bool SudokuSolverBacktracking::solve_puzzle(int linear_ind) {
  // Find the first empty slot starting at linearInd.
  while (linear_ind < N * N && !_board->is_empty(linear_ind)) {
    ++linear_ind;
  }

  // If empty slot is past puzzle boundary - we won!
  if (linear_ind >= N * N) {
    return true;
  }

  bool success{0};

  // Try guessing the value at that slot
  for (int guess{1}; guess <= 9; ++guess) {
    // Check if the guess is valid
    if (!_board->is_guess_valid(linear_ind, guess)) {
      continue;
    }

    // If it is a valid guess - try it.
    _board->guess(linear_ind, guess);
    success = solve_puzzle(linear_ind + 1);
    if (success) {
      return true;
    }
  }

  // If we got to the end - there is no valid guess here that works.
  //  - Reset the slot to 0 (empty)
  //  - Backtrace by returning false.
  _board->guess(linear_ind, 0);
  return false;
}

bool SudokuSolverBacktracking::solve_puzzle() { return solve_puzzle(0); }
}  // namespace sudoku
