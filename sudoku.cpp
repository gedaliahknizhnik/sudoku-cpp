#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>
#include <cassert>

// TODO: Check for valid puzzle before starting
// TODO: Efficiency upgrades (std::array copying, etc.)
// TODO: Reading in files?

constexpr int N{9};
constexpr int BOARDSUM{45 * N};

using rowType = std::array<int, N>;

// Overload print operator for std::array
std::ostream &operator<<(std::ostream &out, rowType row)
{
    std::cout << "[ ";
    for (auto x : row)
    {
        std::cout << x << " ";
    }
    std::cout << "]";

    return out;
}

class SudokuBoard
{

public:
    // Standard constructor
    SudokuBoard()
    {
        generateSudokuBoard();
    }

    // Copy constructor (note that this is a deep copy)
    SudokuBoard(const SudokuBoard &board)
        : grid{board.grid}
    {
    }

    // Overload access operator.
    //  - SudokuBoard[x] will return a std::array reference.
    //  - SudokuBoard[x][y] will return a reference to a single int entry.
    rowType &operator[](int index)
    {
        return grid[index];
    }

    // Overloaded print operation.
    friend std::ostream &operator<<(std::ostream &out, SudokuBoard &board)
    {
        for (int ii{0}; ii < N; ++ii)
        {
            std::cout << board[ii] << "\n";
        }

        return out;
    }

    // Extract column as std::array
    rowType getColumn(int x)
    {
        rowType col{};
        for (int jj{0}; jj < N; ++jj)
        {
            col[jj] = grid[jj][x];
        }
        return col;
    }

    // Extract square as std::array
    rowType getSquare(int x, int y)
    {
        rowType square{};
        int index{0};

        // FIXME: Use of number 3
        for (int ii{0}; ii < 3; ++ii)
        {
            for (int jj{0}; jj < 3; ++jj)
            {
                square[index++] = grid[3 * x + ii][3 * y + jj];
            }
        }
        return square;
    }
    rowType getSquare(int linearInd)
    {
        int row{indToRow(linearInd)};
        int col{indToCol(linearInd)};

        return getSquare(row / 3, col / 3);
    }

    // Check if a guess is valid
    bool isGuessValid(int linearInd, int guess)
    {
        assert(guess > 0 && guess <= 9);

        // Check if guess exists in row
        auto row{grid[indToRow(linearInd)]};
        auto itR{std::find(row.begin(), row.end(), guess)};

        if (itR != row.end())
        {
            return false;
        }

        // Check if guess exists in column
        auto col{getColumn(indToCol(linearInd))};
        auto itC{std::find(col.begin(), col.end(), guess)};

        if (itC != col.end())
        {
            return false;
        }

        // Check if guess e>xists in square
        auto square{getSquare(linearInd)};
        auto itS{std::find(square.begin(), square.end(), guess)};

        if (itS != square.end())
        {
            return false;
        }

        // If the guess doesn't exist anywhere else in row, col, square
        // - it's a valid guess.
        return true;
    }

    // Check if a cell is empty.
    bool isEmpty(int row, int col)
    {
        return grid[row][col] == 0;
    }
    bool isEmpty(int linearInd)
    {
        return isEmpty(indToRow(linearInd), indToCol(linearInd));
    }

    // Check for a valid array
    static bool isArrayValid(rowType row)
    {
        std::sort(row.begin(), row.end());
        for (int ii{1}; ii <= N; ++ii)
        {
            if (row[ii - 1] != ii)
                return false;
        }

        return true;
    }

    // Check for a complete and winning puzzle
    bool isPuzzleValid()
    {

        // Check for invalid ROWS
        for (int ii{0}; ii < N; ++ii)
        {
            if (!isArrayValid(grid[ii]))
                return false;
        }

        // Check for invalid COLUMNS
        for (int ii{0}; ii < N; ++ii)
        {
            if (!isArrayValid(getColumn(ii)))
                return false;
        }

        // Check for invalid SQUARES
        // FIXME: Use of number 3
        for (int ii{0}; ii < 3; ++ii)
        {
            for (int jj{0}; jj < 3; ++jj)
            {
                if (!isArrayValid(getSquare(ii, jj)))
                    return false;
            }
        }

        return true;
    }

    // Check if all grid entries are complete by summing over the whole board.
    //  - sum < BOARDSUM -> empty slots
    //  - sum > BOARDSUM -> Invalid entries
    // FIXME: This is not valid - what if other entries that sum to 45?
    bool isFull()
    {
        int sum{0};

        for (auto row : grid)
        {
            sum += std::accumulate(row.begin(), row.end(), 0);
        }

        return sum == BOARDSUM;
    }

    // Solve the puzzle
    bool solvePuzzle();
    bool solvePuzzle(int linearInd);

private:
    std::array<rowType, N> grid{};

    // Generate the initial board. Currently just a static puzzle.
    void generateSudokuBoard()
    {
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
        int sampleGrid[N][N] = {{0, 3, 0, 0, 0, 0, 9, 0, 0},
                                {0, 2, 7, 5, 0, 0, 6, 0, 3},
                                {6, 0, 9, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 1, 0, 7, 0},
                                {3, 0, 0, 0, 8, 0, 0, 0, 0},
                                {1, 0, 5, 7, 0, 0, 0, 2, 0},
                                {0, 0, 0, 0, 0, 5, 8, 0, 0},
                                {0, 5, 0, 2, 4, 0, 0, 9, 0},
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

        for (int ii{0}; ii < N; ++ii)
        {
            for (int jj{0}; jj < N; ++jj)
            {
                grid[ii][jj] = sampleGrid[ii][jj];
            }
        }
    }

    // Convert linear index to row index
    int indToRow(int x)
    {
        assert(x < N * N);
        return x / N;
    }

    // Convert linear index to col index
    int indToCol(int x)
    {
        assert(x < N * N);
        return x % N;
    }

    // Guess using linear index
    void guessAtInd(int linearInd, int guess)
    {
        grid[indToRow(linearInd)][indToCol(linearInd)] = guess;
    }
};

bool SudokuBoard::solvePuzzle(int linearInd)
{
    // std::cout << *this << "\n";

    // Find the first empty slot starting at linearInd.
    while (linearInd < N * N && !isEmpty(linearInd))
    {
        ++linearInd;
    }

    // If empty slot is past puzzle boundary - we won!
    if (linearInd >= N * N)
    {
        return true;
    }

    bool success{0};

    // Try guessing the value at that slot
    for (int guess{1}; guess <= 9; ++guess)
    {
        // std::cout << "Guessing at index " << linearInd << ", value " << guess;

        // Check if the guess is valid
        if (!isGuessValid(linearInd, guess))
        {
            // std::cout << ", which isn't valid.\n";
            continue;
        }

        // std::cout << ", which is valid!\n";

        // If it is a valid guess - try it.
        guessAtInd(linearInd, guess);
        success = solvePuzzle(linearInd + 1);
        if (success)
        {
            return true;
        }
    }

    // If we got to the end - there is no valid guess here that works.
    //  - Reset the slot to 0 (empty)
    //  - Backtrace by returning false.
    guessAtInd(linearInd, 0);
    // std::cout << "\t Resetting index " << linearInd << "\n";
    return false;
}

bool SudokuBoard::solvePuzzle()
{
    return solvePuzzle(0);
}

int main()
{

    std::cout << "Sudoku time..."
              << "\n\n";

    SudokuBoard s{};

    std::cout << "Starting puzzle: \n"
              << s << "\n";
    std::cout << "Solving puzzle...\n";

    bool success{s.solvePuzzle()};

    if (success)
    {
        std::cout << "Solved the puzzle!\n"
                  << s << "\n";
    }
    else
    {
        std::cout << "No solution found...\n";
    }

    return 0;
}