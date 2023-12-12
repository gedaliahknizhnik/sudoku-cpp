#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <iostream>
#include <string_view>

constexpr int N{9};
constexpr int BOARDSUM{45 * N};

using rowType = std::array<int, N>;
using gridType = std::array<rowType, N>;

// Overload print operator for std::array
std::ostream &operator<<(std::ostream &out, const rowType row);

class SudokuBoard {
 public:
  SudokuBoard(const std::string_view file_name);

  // Copy constructor (note that this is a deep copy)
  SudokuBoard(const SudokuBoard &board);

  // Overload access operator.
  //  - SudokuBoard[x] will return a std::array reference.
  //  - SudokuBoard[x][y] will return a reference to a single int entry.
  rowType &operator[](const int index);
  rowType &operator[](const int index) const;

  // Overloaded print operation.
  friend std::ostream &operator<<(std::ostream &out, SudokuBoard &board);

  // Extract column as std::array
  rowType get_column(const int x);

  // Extract square as std::array
  rowType get_square(const int x, const int y);
  rowType get_square(const int linearInd);

  // Check if a guess is valid
  bool is_guess_valid(const int linearInd, const int guess);
  // Check if a cell is empty.
  bool is_empty(const int row, const int col);
  bool is_empty(const int linearInd);

  // Check for a complete and winning puzzle
  bool is_puzzle_valid();

  // Guess using linear index
  void guess_at_ind(const int linearInd, const int guess);

 private:
  gridType _grid{};

  void load_board_from_file(const std::string_view file_name);

  int ind_to_row(const int x);  // Convert linear index to row index
  int ind_to_col(const int x);  // Convert linear index to col index

  // Check for a valid array
  static bool is_array_valid(rowType row);
};

#endif
