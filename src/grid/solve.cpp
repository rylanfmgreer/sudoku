
#include "sudoku_grid.hpp"
#include <algorithm>

namespace Sudoku
{
    
    void SudokuGrid::solve()
    {
        // If already solved, return
        if(isSolved())
            return;

        // just putting in all the easy wins first significantly speeds up the solving process
        applyAllDeductiveReasoning(); // right now just the easy wins

        // now we apply a backtracking algo where we try all possible values for the next empty cell
        // and then all of them for the next cell, etc try to solve from there
        std::vector<SudokuGrid> next_grids = getNextGrids();
        for(auto& next_grid : next_grids)
        {
            next_grid.solve();
            if(next_grid.isSolved())
            {
                copyFrom(next_grid);
                return;
            }
        }
        return; // return an empty Grid if no solution found
    }

    std::vector<SudokuGrid> SudokuGrid::helperGetNextGrids(IndexInt r, IndexInt c) const
    {
        /*
            This function generates all possible next grids by trying all possible values
            for the given empty cell (r, c) and returns them in a vector.
        */
        std::vector<SudokuGrid> next_grids;
        next_grids.reserve(9);
        getPossibleValuesForEasyWins(r, c);
        for(IndexInt val = 1; val <= 9; ++val)
        {
            if(!m_possible_values_helper->possible_values[val - 1])
                continue;
            else
            {
                SudokuGrid new_grid(*this);
                new_grid.set(r, c, val);
                next_grids.push_back(new_grid);
            }
        }
        return next_grids;
    }

    void SudokuGrid::findNextEmptyCell() const
    {
        m_next_empty_cell_helper->next_empty_row = -1;
        m_next_empty_cell_helper->next_empty_col = -1;
        for(int r = 0; r < 9; ++r)
        {
            for(int c = 0; c < 9; ++c)
            {
                if(get(r, c) == 0)
                {
                    m_next_empty_cell_helper->next_empty_row = r;
                    m_next_empty_cell_helper->next_empty_col = c;
                    return;
                }
            }
        }
    }

    std::vector<SudokuGrid> SudokuGrid::getNextGrids(IndexInt r, IndexInt c) const
    {
        if(r == -1 || c == -1)
        {
            SudokuGrid temp_grid(*this);
            temp_grid.findNextEmptyCell();
            if(temp_grid.m_next_empty_cell_helper->next_empty_row == -1 || temp_grid.m_next_empty_cell_helper->next_empty_col == -1)
            {
                return std::vector<SudokuGrid>();
            }
            r = temp_grid.m_next_empty_cell_helper->next_empty_row;
            c = temp_grid.m_next_empty_cell_helper->next_empty_col;
        }
        return helperGetNextGrids(r, c);
    }

} // namespace Sudoku