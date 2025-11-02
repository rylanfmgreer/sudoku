#include <iostream>
#include "src/grid/sudoku_grid.hpp"
#include "src/grid_reader/grid_reader.hpp"
#include "src/solver_wrapper/solver_wrapper.hpp"

int main()
{
    const char* filename = "grids.txt";
    int solved_count = Sudoku::solve_grids_from_file(filename, true);
    return 0;
}