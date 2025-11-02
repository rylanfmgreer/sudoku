#ifndef _SOLVER_WRAPPER_HPP_
#define _SOLVER_WRAPPER_HPP_
#include "../grid_reader/grid_reader.hpp"
#include "../grid/sudoku_grid.hpp"

namespace Sudoku
{
    long int current_time();
    bool solve_single_grid(SudokuGrid& grid, bool verbose=true);
    int solve_vector_of_grids(std::vector<SudokuGrid>& grids, bool verbose=true);
    int solve_grids_from_file(const char* filename, bool verbose=true);
} // namespace Sudoku


#endif