#ifndef GRID_READER_HPP
#define GRID_READER_HPP
#include <string>
#include <vector>
#include "../grid/sudoku_grid.hpp"

namespace Sudoku
{
    /**
     * @brief Read Sudoku grids from a file
     * 
     * The file is expected to have grids in the following format:
     * 
     * Grid 01
     * 003020600
     * 900305001
     * 001806400
     * 008102900
     * 700000008
     * 006708200
     * 002609500
     * 800203009
     * 005010300
     * 
     * Each grid starts with a line "Grid ____" followed by 9 lines of 9 digits each (0-9),
     * where 0 represents an empty cell.
     *
     * @param filename The name of the file to read from
     * @return A vector of SudokuGrid objects read from the file
     */
    std::vector<SudokuGrid> readGridsFromFile(const char* filename);
} // namespace Sudoku
#endif