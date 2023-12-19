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
 * @brief Sudoku related values
 */
namespace sudoku {

// CONSTANTS *******************************************************************

constexpr int N{9};              ///< Size of sudoku board
constexpr int n{3};              ///< Size of small sudoku square
constexpr int BOARDSUM{45 * N};  ///< Total sum of numbers on a full board

// VARIABLE ALIASES ************************************************************

using row_type = std::array<int, N>;        ///< Alias for a row
using grid_type = std::array<row_type, N>;  ///< Alias for a sudoku board

/**
 * @brief Overload print operator for row of a sudoku board (std::array).
 *
 * @param out Output stream.
 * @param row The row to be printed.
 * @return std::ostream& Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &out, const row_type row);

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
   * @brief Construct a sudoku board from a CSV file.
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

  /**
   * @brief Construct a sudoku board from another Sudoku board, via a deep copy.
   * @overload
   *
   * @param board
   *   const SudokuBoard reference that is deep copied.
   */
  SudokuBoard(const SudokuBoard &board);

  /**
   * @brief Overloaded access operator
   *
   * - SudokuBoard[x] returns a std::array reference to a row of the board
   * - SudokuBoard[x][y] returns a reference to a single entry in the board.
   *
   * @param index
   *   const int index at which to evaluate
   */
  row_type &operator[](const int index);

  /**
   * @brief Overload print operation.
   *
   * @param out Output stream.
   * @param board SudokuBoard reference to be printed.
   * @return std::ostream& Reference to the output stream.
   */
  friend std::ostream &operator<<(std::ostream &out, SudokuBoard &board);

  /**
   * @brief Extract a column of the board as a std::array
   *
   * This does **not** modify the internal board representation or give access
   * to it.
   *
   * @param x
   *    const int index of hte column [0,9)
   *
   * @return row_type Extracted column as std::array.
   */
  row_type get_column(const int x) const;

  /**
   * @brief Extract a square of the board as a std::array
   *
   * This does **not** modify the internal board representation or give access
   * to it.
   *
   * @param x
   *    const int row index of the square [0,3)
   * @param y
   *    const int column index of the square [0,3)
   *
   * @return row_type Extracted square as std::array.
   */
  row_type get_square(const int x, const int y) const;
  /**
   * @brief Extract a square of the board as a std::array. @overload
   *
   * This does **not modify the internal board representation or give access to
   * it.
   *
   * @param linearInd
   *   const int index of squares from 0 to 9.
   *
   * @return row_type Extracted square as std::array.
   */
  row_type get_square(const int linear_ind) const;

  /**
   * @brief Check if a guess is valid (aka it does not result in an invalid
   * board)
   *
   * Note that this function does **not** actually make the guess. I.e. it does
   * not modify the sudoku board.
   * @param linear_ind
   *     const int linear index at which to make the guess
   * @param guess
   *     const int value to guess [0,9]
   *
   * @return true - the guess is safe (this number is not found in the row,
   * column, square)
   * @return false - teh guess is unsafe
   */
  bool is_guess_valid(const int linear_ind, const int guess) const;

  /**
   * @brief Check if a cell is available for guessing
   *
   * @param row
   *     const int row index into the board
   * @param col
   *     const int column index into the board
   *
   * @return true - the cell is empty
   * @return false - the cell is not empty
   */
  bool is_empty(const int row, const int col) const;
  /**
   * @brief Check if a cell is available for guessing. @overload
   *
   * @param linear_ind
   *     const int linear index into the board
   *
   * @return true - the cell is empty
   * @return false - the cell is not empty
   */
  bool is_empty(const int linear_ind) const;

  /**
   * @brief Check if the puzzle is valid/complete.
   *
   * If `for_win = true`, this function checks if the puzzle is complete. I.e.
   * it checks if every row/column/square contains all the numbers just once.
   *
   * If `for_win = false`, this function checks that no number (other than zero,
   * which represents an empty cell) is repeated more than once in any
   * row/column/square.
   *
   * @param for_wind
   *     boolean indicator of checking for win or for loading
   *
   * @return true - puzzle is solved (for_win=true) or valid (for_win=false)
   * @return false - puzzle is not solved (for_win=true) or not valid
   * (for_win=false)
   */
  bool is_puzzle_valid(const bool for_win = false) const;

  /**
   * @brief Make a guess in the puzzle.
   *
   * @param linear_ind
   *    const int linear index at which to make the guess
   * @param guess
   *    const int guess to make [0, 9]
   */
  void guess(const int linear_ind, const int guess);
  /**
   * @brief Make a guess in the puzzle. @overload
   *
   * @param row
   *     const int row index at which to make the guess
   * @param col
   *     const int column index at which to make the guessing
   * @param guess
   *     const int guess to make [0, 9]
   */
  void guess(const int row, const int col, const int guess);

 private:
  grid_type _grid{};  ///< Internal representation of the puzzle

  /**
   * @brief Load a puzzle from a CSV file passed by name
   *
   * @param file_name
   *     string_view of the puzzle file name WITH the path to it from the
   *        current directory
   *
   * @exception - std::runtime_exception() puzzle file cannot be found.
   * @exception - std::runtime_exception() puzzle file is not a 9x9 CSV.
   * @exception - std::runtime_exception() puzzle file contains an invalid
   * puzzle.
   */
  void load_board_from_file(const std::string_view file_name);

  /**
   * @brief Convert linear index to row value
   *
   * @param x
   *     const int linear index to convert
   * @return int row index in the puzzle grid
   */
  int ind_to_row(const int x) const;  // Convert linear index to row index
  /**
   * @brief Convert linear index to column value
   *
   * @param x
   *     const int linear index to convert
   * @return int column index in the puzzle grid
   */
  int ind_to_col(const int x) const;  // Convert linear index to col index

  // Check for a valid array
  /**
   * @brief Check that an array is valid (could be row, column, or square)
   *
   * If `for_win=true` - the check is for an array that contains all numbers
   * [1,9] only once.
   *
   * If `for_win=true` - the check is for an array that contains no duplicates
   * of any number > 0. The array may contain multiples of zero, which
   * represents an empty cell.
   *
   * @param row
   *     row_type representation of row, column, or square (is modified during
   * the check)
   * @param for_win
   *     boolean that determines check type
   *
   * @return true - the array is valid
   * @return false - the array is invalid
   */
  static bool is_array_valid(row_type row, const bool for_win);
};
}  // namespace sudoku
#endif
