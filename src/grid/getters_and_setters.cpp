#include "sudoku_grid.hpp"

namespace Sudoku
{
    int& SudokuGrid::get(int r, int c) const
    {
        return m_grid[r * GRID_ROW_SIZE + c];
    }
    
    void SudokuGrid::set(int r, int c, int val)
    {
        get(r, c) = val;
    }
}