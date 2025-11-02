#include "sudoku_grid.hpp"

namespace Sudoku
{
    bool SudokuGrid::isSolved() const
    {
        return allGridEntriesAreFilledIn() && totalGridIsLegal();
    }

    bool SudokuGrid::thisGridIsLegal(IndexInt r, IndexInt c) const
    {
        clearSeen();
        return thisRowIsLegal(r) && thisColumnIsLegal(c) && thisSquareIsLegal(r, c);
    }

    bool SudokuGrid::allGridEntriesAreFilledIn() const
    {
        // Check if there are any zero entries in the grid
        // We start from the back of the grid because in solving, 
        // we tend to fill in the front first, so zeros are more likely to be at the end
        for(ValueInt* ptr = m_grid + N_GRID_CELLS - 1; ptr != m_grid; --ptr)
        {
            if(*ptr == 0)
                return false;
        }
        return true;
    }
    
    bool SudokuGrid::thisRowIsLegal(IndexInt r) const
    {
        /// Check if the current row is legal by ensuring all numbers are unique
        clearSeen();
        for(int idx = r * GRID_ROW_SIZE; idx < (r + 1) * GRID_ROW_SIZE; ++idx)
        {
            int val = m_grid[idx];
            if(val == 0)
                continue; // skip empty cells
            if(m_possible_values_helper.seen[val - 1])
                return false;
            m_possible_values_helper.seen[val - 1] = true;
        }
        return true;
    }

    bool SudokuGrid::allRowsAreLegal() const
    {
        for(int row = 0; row < 9; ++row)
        {
            if(!thisRowIsLegal(row))
                return false;
        }
        return true;
    }

    bool SudokuGrid::thisColumnIsLegal(IndexInt c) const
    {
        clearSeen();
        for(IndexInt row = 0; row < 9; ++row)
        {
            ValueInt val = m_grid[row * GRID_ROW_SIZE + c];
            if(val == 0)
                continue; // skip empty cells
            if(m_possible_values_helper.seen[val - 1])
                return false;
            m_possible_values_helper.seen[val - 1] = true;
        }
        return true;
    }

    bool SudokuGrid::allColumnsAreLegal() const
    {
        for(IndexInt col = 0; col < 9; ++col)
        {
            if(!thisColumnIsLegal(col))
                return false;
        }
        return true;
    }

    bool SudokuGrid::thisSquareIsLegal(IndexInt r, IndexInt c) const
    {
        clearSeen();
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
                if(m_possible_values_helper.seen[val - 1])
                    return false;
                m_possible_values_helper.seen[val - 1] = true;
            }
        }
        return true;
    }

    bool SudokuGrid::allSquaresAreLegal() const
    {
        for(int box_row = 0; box_row < 3; ++box_row)
        {
            for(int box_col = 0; box_col < 3; ++box_col)
            {
                int start_r = box_row * 3;
                int start_c = box_col * 3;
                if(!thisSquareIsLegal(start_r, start_c))
                    return false;
            }
        }
        return true;
    }

    bool SudokuGrid::totalGridIsLegal() const
    {
        // A grid is legal if all rows, columns, and squares are legal
        // We do rows first for potential speed benefits, as we are
        // guessing values by rows. (Not clear if this will actually help given other optimizations)
        clearSeen();
        return allRowsAreLegal() && allColumnsAreLegal() && allSquaresAreLegal();
    }
    
} // namespace Sudoku
