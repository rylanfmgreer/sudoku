#include <iostream>
#include "src/grid/sudoku_grid.hpp"
#include "src/grid_reader/grid_reader.hpp"
#include "src/solver_wrapper/solver_wrapper.hpp"

int main(int argc, char** argv)
{
    // default filename
    const char* filename = "grids.txt";
    if(argc > 1) filename = argv[1];
    int solved_count = Sudoku::solveGridsFromFile(filename, true);
    return 0;
}