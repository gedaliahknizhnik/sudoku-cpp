#include "sudoku.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

// TODO: Check for valid puzzle before starting
// TODO: Efficiency upgrades (std::array copying, etc.)
//  TODO: Use iterators to go over the columns and squares.
// TODO: Reading in files?
// TODO: Check for unneeded functions

using rowType = std::array<int, N>;
using gridType = std::array<rowType, N>;

// Overload print operator for std::array
std::ostream &operator<<(std::ostream &out, rowType row) {
  std::cout << "[ ";
  for (auto x : row) {
    std::cout << x << " ";
  }
  std::cout << "]";

  return out;
}

// Standard constructor
SudokuBoard::SudokuBoard() { generate_sudoku_board(); }

// Copy constructor (note that this is a deep copy)
SudokuBoard::SudokuBoard(const SudokuBoard &board) : _grid{board._grid} {}

// Overload access operator.
//  - SudokuBoard[x] will return a std::array reference.
//  - SudokuBoard[x][y] will return a reference to a single int entry.
rowType &SudokuBoard::operator[](int index) { return _grid[index]; }

// Overloaded print operation.
std::ostream &operator<<(std::ostream &out, SudokuBoard &board) {
  for (int ii{0}; ii < N; ++ii) {
    std::cout << board[ii] << "\n";
  }

  return out;
}

// Extract column as std::array
rowType SudokuBoard::get_column(int x) {
  rowType col{};
  for (int jj{0}; jj < N; ++jj) {
    col[jj] = _grid[jj][x];
  }
  return col;
}

// Extract square as std::array
rowType SudokuBoard::get_square(int x, int y) {
  rowType square{};
  int index{0};

  for (int ii{0}; ii < 3; ++ii) {
    for (int jj{0}; jj < 3; ++jj) {
      square[index++] = _grid[3 * x + ii][3 * y + jj];
    }
  }
  return square;
}
rowType SudokuBoard::get_square(int linearInd) {
  int row{ind_to_row(linearInd)};
  int col{ind_to_col(linearInd)};

  return get_square(row / 3, col / 3);
}

// Check if a guess is valid
bool SudokuBoard::is_guess_valid(int linearInd, int guess) {
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
bool SudokuBoard::is_empty(int row, int col) { return _grid[row][col] == 0; }
bool SudokuBoard::is_empty(int linearInd) {
  return is_empty(ind_to_row(linearInd), ind_to_col(linearInd));
}

// Check for a complete and winning puzzle
bool SudokuBoard::is_puzzle_valid() {
  // Check for invalid ROWS
  for (int ii{0}; ii < N; ++ii) {
    if (!is_array_valid(_grid[ii])) return false;
  }

  // Check for invalid COLUMNS
  for (int ii{0}; ii < N; ++ii) {
    if (!is_array_valid(get_column(ii))) return false;
  }

  // Check for invalid SQUARES
  // FIXME: Use of number 3
  for (int ii{0}; ii < 3; ++ii) {
    for (int jj{0}; jj < 3; ++jj) {
      if (!is_array_valid(get_square(ii, jj))) return false;
    }
  }

  return true;
}

// Generate the initial board. Currently just a static puzzle.
void SudokuBoard::generate_sudoku_board() {
  // Easy Puzzle to solve
  // int sampleGrid[N][N] = {{0, 6, 2, 0, 3, 7, 5, 0, 0},
  //                         {0, 8, 5, 0, 0, 2, 0, 6, 0},
  //                         {0, 0, 4, 0, 0, 0, 0, 0, 0},
  //                         {0, 0, 6, 0, 8, 3, 0, 0, 1},
  //                         {0, 0, 3, 0, 1, 9, 4, 8, 0},
  //                         {0, 0, 0, 5, 0, 4, 6, 9, 0},
  //                         {0, 2, 7, 0, 0, 0, 9, 4, 5},
  //                         {0, 4, 9, 0, 2, 0, 0, 3, 8},
  //                         {5, 0, 0, 4, 9, 8, 0, 0, 6}};

  // Medium Puzzle to solve
  // int sampleGrid[N][N] = {{4, 0, 0, 0, 1, 0, 0, 8, 0},
  //                         {0, 0, 0, 0, 0, 0, 0, 0, 3},
  //                         {9, 1, 7, 0, 0, 3, 0, 5, 0},
  //                         {8, 0, 5, 0, 3, 0, 0, 0, 0},
  //                         {1, 0, 0, 7, 0, 4, 0, 0, 0},
  //                         {0, 7, 4, 0, 9, 0, 0, 0, 2},
  //                         {2, 9, 0, 8, 7, 0, 0, 4, 5},
  //                         {0, 0, 0, 2, 0, 0, 0, 0, 0},
  //                         {5, 0, 0, 3, 0, 0, 7, 0, 6}};

  // Hard Puzzle to solve
  int sampleGrid[N][N] = {
      {0, 3, 0, 0, 0, 0, 9, 0, 0}, {0, 2, 7, 5, 0, 0, 6, 0, 3},
      {6, 0, 9, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 7, 0},
      {3, 0, 0, 0, 8, 0, 0, 0, 0}, {1, 0, 5, 7, 0, 0, 0, 2, 0},
      {0, 0, 0, 0, 0, 5, 8, 0, 0}, {0, 5, 0, 2, 4, 0, 0, 9, 0},
      {0, 0, 0, 3, 0, 0, 0, 0, 0}};

  // Super Hard Puzzle to solve (this is a worst case puzzle
  //  because the first digit is a 9...)
  // int sampleGrid[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
  //                         {0, 0, 0, 0, 0, 3, 0, 8, 5},
  //                         {0, 0, 1, 0, 2, 0, 0, 0, 0},
  //                         {0, 0, 0, 5, 0, 7, 0, 0, 0},
  //                         {0, 0, 4, 0, 0, 0, 1, 0, 0},
  //                         {0, 9, 0, 0, 0, 0, 0, 0, 0},
  //                         {5, 0, 0, 0, 0, 0, 0, 7, 3},
  //                         {0, 0, 2, 0, 1, 0, 0, 0, 0},
  //                         {0, 0, 0, 0, 4, 0, 0, 0, 9}};

  // Solved puzzle
  // int sampleGrid[N][N] = {{4, 3, 5, 2, 6, 9, 7, 8, 1},
  //                         {6, 8, 2, 5, 7, 1, 4, 9, 3},
  //                         {1, 9, 7, 8, 3, 4, 5, 6, 2},
  //                         {8, 2, 6, 1, 9, 5, 3, 4, 7},
  //                         {3, 7, 4, 6, 8, 2, 9, 1, 5},
  //                         {9, 5, 1, 7, 4, 3, 6, 2, 8},
  //                         {5, 1, 9, 3, 2, 6, 8, 7, 4},
  //                         {2, 4, 8, 9, 5, 7, 1, 3, 6},
  //                         {7, 6, 3, 4, 1, 8, 2, 5, 9}};

  for (int ii{0}; ii < N; ++ii) {
    for (int jj{0}; jj < N; ++jj) {
      _grid[ii][jj] = sampleGrid[ii][jj];
    }
  }
}

// Convert linear index to row index
int SudokuBoard::ind_to_row(int x) {
  assert(x < N * N);
  return x / N;
}

// Convert linear index to col index
int SudokuBoard::ind_to_col(int x) {
  assert(x < N * N);
  return x % N;
}

// Guess using linear index
void SudokuBoard::guess_at_ind(int linearInd, int guess) {
  _grid[ind_to_row(linearInd)][ind_to_col(linearInd)] = guess;
}

// Check for a valid array TODO: Should this be const by reference?
bool SudokuBoard::is_array_valid(rowType row) {
  std::sort(row.begin(), row.end());
  for (int ii{1}; ii <= N; ++ii) {
    if (row[ii - 1] != ii) return false;
  }

  return true;
}


