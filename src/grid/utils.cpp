#include "sudoku_grid.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
namespace Sudoku
{
    void SudokuGrid::print() const
    {
        for(int r = 0; r < 9; ++r)
        {
            for(int c = 0; c < 9; ++c)
            {
                std::cout << get(r, c) << " ";
            }
            std::cout << std::endl;
        }
    }
    void SudokuGrid::clearSeen()
    {
        std::fill(m_seen, m_seen + 9, false);
    }

    void SudokuGrid::copyFrom(const SudokuGrid& other)
    {
        std::copy(other.m_grid, other.m_grid + N_GRID_CELLS, m_grid);
    }
    
} // namespace Sudoku
