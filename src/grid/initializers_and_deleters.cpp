#include "sudoku_grid.hpp"
namespace Sudoku
{
    SudokuGrid::SudokuGrid()
    : m_next_empty_row(-1), m_next_empty_col(-1)
    {
        m_grid = new int[N_GRID_CELLS];
    }

    SudokuGrid::SudokuGrid(const SudokuGrid& other):
    m_next_empty_row(other.m_next_empty_row),
    m_next_empty_col(other.m_next_empty_col)
    {
        m_grid = new int[N_GRID_CELLS];
        copyFrom(other);
    }

    SudokuGrid::~SudokuGrid()
    {
        delete[] m_grid;
    }

} // namespace Sudoku
