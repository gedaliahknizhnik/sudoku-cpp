#include "sudoku.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>

#include "rapidcsv.h"
namespace sudoku {
using row_type = std::array<int, N>;
using grid_type = std::array<row_type, N>;

// Overload print operator for std::array
std::ostream &operator<<(std::ostream &out, const row_type row) {
  std::cout << "[ ";
  for (auto x : row) {
    std::cout << x << " ";
  }
  std::cout << "]";

  return out;
}

// Standard constructor
SudokuBoard::SudokuBoard(const std::string_view file_name) {
  load_board_from_file(file_name);
}

// Copy constructor (note that this is a deep copy)
SudokuBoard::SudokuBoard(const SudokuBoard &board) : _grid{board._grid} {}

// Overload access operator.
//  - SudokuBoard[x] will return a std::array reference.
//  - SudokuBoard[x][y] will return a reference to a single int entry.
row_type &SudokuBoard::operator[](const int index) { return _grid[index]; }

// Overloaded print operation.
std::ostream &operator<<(std::ostream &out, SudokuBoard &board) {
  for (int ii{0}; ii < N; ++ii) {
    std::cout << board[ii] << "\n";
  }

  return out;
}

// Extract column as std::array
row_type SudokuBoard::get_column(const int x) const {
  row_type col{};
  for (int jj{0}; jj < N; ++jj) {
    col[jj] = _grid[jj][x];
  }
  return col;
}

// Extract square as std::array
row_type SudokuBoard::get_square(const int x, const int y) const {
  row_type square{};
  int index{0};

  for (int ii{0}; ii < 3; ++ii) {
    for (int jj{0}; jj < 3; ++jj) {
      square[index++] = _grid[3 * x + ii][3 * y + jj];
    }
  }
  return square;
}
row_type SudokuBoard::get_square(const int linearInd) const {
  int row{ind_to_row(linearInd)};
  int col{ind_to_col(linearInd)};

  return get_square(row / 3, col / 3);
}

// Check if a guess is valid
bool SudokuBoard::is_guess_valid(const int linearInd, const int guess) const {
  assert(guess > 0 && guess <= 9);

  // Check if guess exists in row
  auto row{_grid[ind_to_row(linearInd)]};
  auto itR{std::find(row.begin(), row.end(), guess)};

  if (itR != row.end()) {
    return false;
  }

  // Check if guess exists in column
  auto col{get_column(ind_to_col(linearInd))};
  auto itC{std::find(col.begin(), col.end(), guess)};

  if (itC != col.end()) {
    return false;
  }

  // Check if guess e>xists in square
  auto square{get_square(linearInd)};
  auto itS{std::find(square.begin(), square.end(), guess)};

  if (itS != square.end()) {
    return false;
  }

  // If the guess doesn't exist anywhere else in row, col, square
  // - it's a valid guess.
  return true;
}

// Check if a cell is empty.
bool SudokuBoard::is_empty(const int row, const int col) const {
  return _grid[row][col] == 0;
}
bool SudokuBoard::is_empty(const int linearInd) const {
  return is_empty(ind_to_row(linearInd), ind_to_col(linearInd));
}

// Check for a complete and winning puzzle
bool SudokuBoard::is_puzzle_valid(const bool for_win) const {
  // Check for invalid ROWS
  for (int ii{0}; ii < N; ++ii) {
    if (!is_array_valid(_grid[ii], for_win)) return false;
  }

  // Check for invalid COLUMNS
  for (int ii{0}; ii < N; ++ii) {
    if (!is_array_valid(get_column(ii), for_win)) return false;
  }

  // Check for invalid SQUARES
  for (int ii{0}; ii < 3; ++ii) {
    for (int jj{0}; jj < 3; ++jj) {
      if (!is_array_valid(get_square(ii, jj), for_win)) return false;
    }
  }

  return true;
}

void SudokuBoard::load_board_from_file(const std::string_view file_name) {
  rapidcsv::Document puzzle_doc(std::string{file_name},
                                rapidcsv::LabelParams(-1, -1));

  if (puzzle_doc.GetColumnCount() != 9) {
    throw std::runtime_error("Puzzle file does not have 9 columns.");
  } else if (puzzle_doc.GetRowCount() != 9) {
    throw std::runtime_error("Puzzle file does not have 9 rows.");
  }

  for (int ii{0}; ii < 9; ++ii) {
    std::vector<int> row = puzzle_doc.GetRow<int>(static_cast<size_t>(ii));
    std::copy(row.begin(), row.end(), _grid[ii].begin());
  }

  if (!is_puzzle_valid()) {
    throw std::runtime_error("Puzzle file contains an invalid puzzle.");
  }
}

// Convert linear index to row index
int SudokuBoard::ind_to_row(const int x) const {
  assert(x < N * N);
  return x / N;
}

// Convert linear index to col index
int SudokuBoard::ind_to_col(const int x) const {
  assert(x < N * N);
  return x % N;
}

// Guess using linear index
void SudokuBoard::guess(const int linearInd, const int guess) {
  _grid[ind_to_row(linearInd)][ind_to_col(linearInd)] = guess;
}
void SudokuBoard::guess(const int row, const int col, const int guess) {
  _grid[row][col] = guess;
}

// Check for a valid array
bool SudokuBoard::is_array_valid(row_type row, const bool for_win) {
  std::sort(row.begin(), row.end());
  if (for_win) {
    for (int ii{1}; ii <= N; ++ii) {
      if (row[ii - 1] != ii) return false;
    }
  } else {
    int curr{-1};
    for (int ii{0}; ii <= N; ++ii) {
      if ((curr != 0) && (row[ii] == curr)) return false;
      curr = row[ii];
    }
  }
  return true;
}
}  // namespace sudoku
