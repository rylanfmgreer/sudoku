#ifndef _SOLVER_WRAPPER_HPP_
#define _SOLVER_WRAPPER_HPP_
#include "../grid_reader/grid_reader.hpp"
#include "../grid/sudoku_grid.hpp"

namespace Sudoku
{
    long int currentTimeInMilliseconds();
    bool solveSingleGrid(SudokuGrid& grid, bool verbose=true);
    int solveVectorOfGrids(std::vector<SudokuGrid>& grids, bool verbose=true);
    int solveGridsFromFile(const char* filename, bool verbose=true);
} // namespace Sudoku


#endif