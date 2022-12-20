#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>

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

    // Check if a cell is empty.
    bool isEmpty(int row, int col)
    {
        return grid[row][col] == 0;
    }

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

private:
    std::array<rowType, N> grid{};

    // Generate the initial board. Currently just a static puzzle.
    void generateSudokuBoard()
    {
        // Puzzle to solve
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
        int sampleGrid[N][N] = {{4, 3, 5, 2, 6, 9, 7, 8, 1},
                                {6, 8, 2, 5, 7, 1, 4, 9, 3},
                                {1, 9, 7, 8, 3, 4, 5, 6, 2},
                                {8, 2, 6, 1, 9, 5, 3, 4, 7},
                                {3, 7, 4, 6, 8, 2, 9, 1, 5},
                                {9, 5, 1, 7, 4, 3, 6, 2, 8},
                                {5, 1, 9, 3, 2, 6, 8, 7, 4},
                                {2, 4, 8, 9, 5, 7, 1, 3, 6},
                                {7, 6, 3, 4, 1, 8, 2, 5, 9}};

        for (int ii{0}; ii < N; ++ii)
        {
            for (int jj{0}; jj < N; ++jj)
            {
                grid[ii][jj] = sampleGrid[ii][jj];
            }
        }
    }
};

int main()
{

    std::cout << "Sudoku time..."
              << "\n\n";

    SudokuBoard s{};
    SudokuBoard s1{s};
    s[0][0] = 3;

    std::cout << s << "\n";
    std::cout << s1 << "\n";

    std::cout << std::boolalpha << s.isPuzzleValid() << "\n";
    std::cout << std::boolalpha << s1.isPuzzleValid() << "\n";

    return 0;
}