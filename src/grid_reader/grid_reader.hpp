#ifndef GRID_READER_HPP
#define GRID_READER_HPP
#include <string>
#include <vector>
#include "../grid/sudoku_grid.hpp"

namespace Sudoku
{
    std::vector<SudokuGrid> read_grids_from_file(const char* filename);
} // namespace Sudoku
#endif