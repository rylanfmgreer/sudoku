#include "sudoku_grid.hpp"

namespace Sudoku
{
    bool SudokuGrid::is_solved()
    {
        return no_zero_entries() && grid_is_ok();
    }

    bool SudokuGrid::no_zero_entries() const
    {
        for(int idx = 0; idx < N_GRID_CELLS; ++idx)
        {
            if(m_grid[idx] == 0)
                return false;
        }
        return true;
    }
    bool SudokuGrid::this_row_is_ok(int r)
    {
        clear_seen();
        for(int idx = r * GRID_ROW_SIZE; idx < (r + 1) * GRID_ROW_SIZE; ++idx)
        {
            int val = m_grid[idx];
            if(val == 0)
                continue; // skip empty cells
            if(m_seen[val - 1])
                return false;
            m_seen[val - 1] = true;
        }
        return true;
    }

    bool SudokuGrid::all_rows_are_ok()
    {
        for(int row = 0; row < 9; ++row)
        {
            if(!this_row_is_ok(row))
                return false;
        }
        return true;
    }

    bool SudokuGrid::this_column_is_ok(int c)
    {
        clear_seen();
        for(int row = 0; row < 9; ++row)
        {
            int val = m_grid[row * GRID_ROW_SIZE + c];
            if(val == 0)
                continue; // skip empty cells
            if(m_seen[val - 1])
                return false;
            m_seen[val - 1] = true;
        }
        return true;
    }

    bool SudokuGrid::all_columns_are_ok()
    {
        for(int col = 0; col < 9; ++col)
        {
            if(!this_column_is_ok(col))
                return false;
        }
        return true;
    }

    bool SudokuGrid::this_square_is_ok(int r, int c)
    {
        clear_seen();
        // box_row and box_col are the index of what box we're checking
        int box_row = r / 3;
        int box_col = c / 3;
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                int val = m_grid[(box_row * 3 + i) * GRID_ROW_SIZE + (box_col * 3 + j)];
                if(val == 0)
                    continue; // skip empty cells
                if(m_seen[val - 1])
                    return false;
                m_seen[val - 1] = true;
            }
        }
        return true;
    }

    bool SudokuGrid::all_squares_are_ok()
    {
        for(int box_row = 0; box_row < 3; ++box_row)
        {
            for(int box_col = 0; box_col < 3; ++box_col)
            {
                int start_r = box_row * 3;
                int start_c = box_col * 3;
                if(!this_square_is_ok(start_r, start_c))
                    return false;
            }
        }
        return true;
    }

    bool SudokuGrid::grid_is_ok()
    {
        return all_rows_are_ok() && all_columns_are_ok() && all_squares_are_ok();
    }
    
} // namespace Sudoku
