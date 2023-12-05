#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <iostream>

// TODO: Check for valid puzzle before starting
// TODO: Efficiency upgrades (std::array copying, etc.)
//  TODO: Use iterators to go over the columns and squares.
// TODO: Reading in files?
// TODO: Check for unneeded functions

constexpr int N{9};
constexpr int BOARDSUM{45 * N};

using rowType = std::array<int, N>;
using gridType = std::array<rowType, N>;

// Overload print operator for std::array
std::ostream &operator<<(std::ostream &out, rowType row);

class SudokuBoard {
 public:
  // Standard constructor (calls generateSudokuBoard)
  SudokuBoard();

  // Copy constructor (note that this is a deep copy)
  SudokuBoard(const SudokuBoard &board);

  // Overload access operator.
  //  - SudokuBoard[x] will return a std::array reference.
  //  - SudokuBoard[x][y] will return a reference to a single int entry.
  rowType &operator[](int index);

  // Overloaded print operation.
  friend std::ostream &operator<<(std::ostream &out, SudokuBoard &board);

  // Extract column as std::array
  rowType get_column(int x);

  // Extract square as std::array
  rowType get_square(int x, int y);
  rowType get_square(int linearInd);

  // Check if a guess is valid
  bool is_guess_valid(int linearInd, int guess);
  // Check if a cell is empty.
  bool is_empty(int row, int col);
  bool is_empty(int linearInd);

  // Check for a complete and winning puzzle
  bool is_puzzle_valid();

  // Solve the puzzle
  bool solve_puzzle();
  bool solve_puzzle(int linearInd);

 private:
  gridType grid{};

  // Generate the initial board. Currently just a static puzzle.
  void generate_sudoku_board();

  int ind_to_row(int x);  // Convert linear index to row index
  int ind_to_col(int x);  // Convert linear index to col index

  // Guess using linear index
  void guess_at_ind(int linearInd, int guess);

  // Check for a valid array
  static bool is_array_valid(rowType row);
};

#endif
