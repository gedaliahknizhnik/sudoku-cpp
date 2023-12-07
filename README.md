# SUDOKU-CPP

**Maintainer**: Gedaliah Knizhnik - gedaliah.knizhnik@gmail.com

---

This is a C++ library for solving Sudoku puzzles. A basic Sudoku board (9x9) class is defined in `sudoku.[c,h]pp`, and the backtracking solver is implemented in `sudoku_solver_backtracking.[c,h]pp`.

Puzzles are loaded in from CSV files. Some examples are provided in the `puzzles/` directory, but feel free to define your own! Zeros stand for empty squares.

To solve a puzzle, build the libraries using:

```bash 
mkdir build && cd build
cmake ..
make
```

Then call the solver main script:

```bash
./solve <path-to-puzzle-file>
```
