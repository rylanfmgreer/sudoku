#include "sudoku_grid.hpp"
namespace Sudoku
{
    SudokuGrid::SudokuGrid()
    {
        m_grid = new ValueInt[N_GRID_CELLS];
    }

    SudokuGrid::SudokuGrid(const SudokuGrid& other):
    m_next_empty_cell_helper(other.m_next_empty_cell_helper),
    m_possible_values_helper(other.m_possible_values_helper)
    {
        m_grid = new ValueInt[N_GRID_CELLS];
        copyFrom(other);
    }

    SudokuGrid::~SudokuGrid()
    {
        delete[] m_grid;
    }

} // namespace Sudoku
