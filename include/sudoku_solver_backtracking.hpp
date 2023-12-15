#ifndef SUDOKU_SOLVER_BACKTRACK_HPP
#define SUDOKU_SOLVER_BACKTRACK_HPP

#include <memory>

#include "sudoku.hpp"
namespace sudoku {
class SudokuSolverBacktracking {
 public:
  SudokuSolverBacktracking(std::shared_ptr<SudokuBoard> board);

  bool solve_puzzle(int linearInd);
  bool solve_puzzle();

 private:
  std::shared_ptr<SudokuBoard> _board;
};
}  // namespace sudoku
#endif
