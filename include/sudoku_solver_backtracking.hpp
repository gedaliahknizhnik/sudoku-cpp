/* @file sudoku_solver_backtracking.hpp
 * @author Gedaliah Knizhnik (gedaliah.knizhnik@gmail.com)
 * @brief A Sudoku Solver that uses backtracking
 * @date 2023-12-18
 *
 * @copyright Copyright (c) 2023
 */

#ifndef SUDOKU_SOLVER_BACKTRACK_HPP
#define SUDOKU_SOLVER_BACKTRACK_HPP

#include <memory>

#include "sudoku.hpp"

/**
 * @brief Sudoku related values
 */
namespace sudoku {

/**
 * @brief A class that implements solving a sudoku puzzle via backtracking.
 *
 * The backtracking algorithm for solving sudoku puzzles involves guessing a
 * digit at each empty spot until the puzzle becomes invalid, then backtracking
 * to the last valid puzzle and guessing a different digit. The algorithm
 * terminates when either all choices have been tried or the end of the puzzle
 * is reached.
 */
class SudokuSolverBacktracking {
 public:
  /**
   * @brief Construct a solver by passing a shared_ptr to the puzzle board. The
   * solver can modify the board but is not responsible for managing its memory.
   */
  SudokuSolverBacktracking(std::shared_ptr<SudokuBoard> board);

  /**
   * @brief Solve the puzzle by starting to guess at the first index.
   *
   * @return true - the puzzle is solved
   * @return false - the puzzle is not solved
   */
  bool solve_puzzle();

 private:
  std::shared_ptr<SudokuBoard>
      _board;  ///< A pointer to the board representation

  /**
   * @brief Solve the puzzle starting from a non-zero linear index. @overload
   *
   * This function is called recursively by the public function `solve_puzzle`.
   */
  bool solve_puzzle(int linearInd);
};
}  // namespace sudoku
#endif
