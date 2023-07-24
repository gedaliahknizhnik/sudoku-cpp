#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>

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
    rowType getColumn(int x);

    // Extract square as std::array
    rowType getSquare(int x, int y);
    rowType getSquare(int linearInd);

    // Check if a guess is valid
    bool isGuessValid(int linearInd, int guess);
    // Check if a cell is empty.
    bool isEmpty(int row, int col);
    bool isEmpty(int linearInd);

    // Check for a complete and winning puzzle
    bool isPuzzleValid();

    // Solve the puzzle
    bool solvePuzzle();
    bool solvePuzzle(int linearInd);

   private:
    gridType grid{};

    // Generate the initial board. Currently just a static puzzle.
    void generateSudokuBoard();

    int indToRow(int x);  // Convert linear index to row index
    int indToCol(int x);  // Convert linear index to col index

    // Guess using linear index
    void guessAtInd(int linearInd, int guess);

    // Check for a valid array
    static bool isArrayValid(rowType row);
};

#endif