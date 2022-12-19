#include <iostream>
#include <array>

constexpr int N{9};

class SudokuBoard
{

public:
    using rowType = std::array<int, N>;

    SudokuBoard()
    {
        std::cout << "Generating board..."
                  << "\n";
        generateSudokuBoard();
    }

    rowType &operator[](int index)
    {
        return grid[index];
    }

    friend std::ostream &operator<<(std::ostream &out, SudokuBoard &board)
    {
        for (int ii{0}; ii < N; ++ii)
        {
            std::cout << "[ ";
            for (int jj{0}; jj < N; ++jj)
            {
                std::cout << board[ii][jj] << " ";
            }
            std::cout << "]\n";
        }

        return out;
    }

private:
    std::array<rowType, N> grid{};

    void generateSudokuBoard()
    {

        int sampleGrid[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 3, 0, 8, 5},
                                {0, 0, 1, 0, 2, 0, 0, 0, 0},
                                {0, 0, 0, 5, 0, 7, 0, 0, 0},
                                {0, 0, 4, 0, 0, 0, 1, 0, 0},
                                {0, 9, 0, 0, 0, 0, 0, 0, 0},
                                {5, 0, 0, 0, 0, 0, 0, 7, 3},
                                {0, 0, 2, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 4, 0, 0, 0, 9}};

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
              << "\n";

    SudokuBoard s{};

    std::cout << s << "\n";
    return 0;
}