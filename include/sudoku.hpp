/**
 * @file sudoku.hpp
 * @author Gedaliah Knizhnik (gedaliah.knizhnik@gmail.com)
 * @brief A Sudoku Board container
 * @date 2023-12-14
 *
 * @copyright Copyright (c) 2023
 */
#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>
#include <iostream>
#include <string_view>

/**
 * @brif Sudoku related values
 */
namespace sudoku {

// CONSTANTS *******************************************************************

constexpr int N{9};              ///< Size of sudoku board
constexpr int n{3};              ///< Size of small sudoku square
constexpr int BOARDSUM{45 * N};  ///< Total sum of numbers on a full board

// VARIABLE ALIASES ************************************************************

using rowType = std::array<int, N>;       ///< Alias for a row
using gridType = std::array<rowType, N>;  ///< Alias for a sudoku board

/**
 * @brief Overloaded print operator for rows of a sudoku board.
 */
std::ostream &operator<<(std::ostream &out, const rowType row);

// SUDOKU **********************************************************************

/**
 * @brief Sudoku Board wrapper class
 *
 * Loads sudoku boards from CSV files and provides methods for solving a puzzle,
 * such as getting rows/columns/squares, guessing at various indices, etc.
 */
class SudokuBoard {
 public:
  /**
   * Construct a sudoku board from a CSV file.
   *
   * @param file_name
   *   string_view full path to the puzzle file from the current directory.
   *
   * @exception - std::runtime_exception() puzzle file cannot be found.
   * @exception - std::runtime_exception() puzzle file is not a 9x9 CSV.
   * @exception - std::runtime_exception() puzzle file contains an invalid
   * puzzle.
   */
  SudokuBoard(const std::string_view file_name);

  // Copy constructor (note that this is a deep copy)
  SudokuBoard(const SudokuBoard &board);

  // Overload access operator.
  //  - SudokuBoard[x] will return a std::array reference.
  //  - SudokuBoard[x][y] will return a reference to a single int entry.
  rowType &operator[](const int index);

  // Overloaded print operation.
  friend std::ostream &operator<<(std::ostream &out, SudokuBoard &board);

  // Extract column as std::array
  rowType get_column(const int x) const;

  // Extract square as std::array
  rowType get_square(const int x, const int y) const;
  rowType get_square(const int linearInd) const;

  // Check if a guess is valid
  bool is_guess_valid(const int linearInd, const int guess) const;

  // Check if a cell is empty.
  bool is_empty(const int row, const int col) const;
  bool is_empty(const int linearInd) const;

  // Check for a complete and winning puzzle
  bool is_puzzle_valid(const bool for_win = false) const;

  // Guess using linear index
  void guess_at_ind(const int linearInd, const int guess);

 private:
  gridType _grid{};

  void load_board_from_file(const std::string_view file_name);

  int ind_to_row(const int x) const;  // Convert linear index to row index
  int ind_to_col(const int x) const;  // Convert linear index to col index

  // Check for a valid array
  static bool is_array_valid(rowType row, const bool for_win);
};
}  // namespace sudoku
#endif
