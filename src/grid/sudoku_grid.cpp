#include "sudoku_grid.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>

namespace Sudoku
{

    void SudokuGrid::solve()
    {
        // If already solved, return
        if(isSolved())
            return;

        // just putting in all the easy wins first significantly speeds up the solving process
        easyWins();

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
        return; // return an empty grid if no solution found
    }

    std::vector<SudokuGrid> SudokuGrid::helperGetNextGrids(int r, int c)
    {
        std::vector<SudokuGrid> next_grids;
        next_grids.reserve(9);
        getPossibleValuesForEasyWins(r, c);
        for(int val = 1; val <= 9; ++val)
        {
            if(!m_possible_values[val - 1])
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

    void SudokuGrid::findNextEmptyCell()
    {
        for(int r = 0; r < 9; ++r)
        {
            for(int c = 0; c < 9; ++c)
            {
                if(get(r, c)  == 0)
                {
                    m_next_empty_row = r;
                    m_next_empty_col = c;
                    return;
                }
            }
        }
        m_next_empty_row = -1;
        m_next_empty_col = -1;
    }

    std::vector<SudokuGrid> SudokuGrid::getNextGrids(int r, int c)
    {
        if(r == -1 || c == -1)
        {
            SudokuGrid temp_grid(*this);
            temp_grid.findNextEmptyCell();
            if(temp_grid.m_next_empty_row == -1 || temp_grid.m_next_empty_col == -1)
            {
                return std::vector<SudokuGrid>();
            }
            r = temp_grid.m_next_empty_row;
            c = temp_grid.m_next_empty_col;
        }
        return helperGetNextGrids(r, c);
    }


    bool SudokuGrid::thisGridIsLegal(int r, int c)
    {
        return thisRowIsLegal(r) && thisColumnIsLegal(c) && thisSquareIsLegal(r, c);
    }

    void SudokuGrid::determineIfThereIsASinglePossibleValueAndSaveIt()
    {
        m_there_is_only_one_possible_value = false;
        m_single_possible_value = -1;
        int count = 0;
        for(int val = 1; val <= 9; ++val)
        {
            if(m_possible_values[val - 1])
            {
                ++count;
                m_single_possible_value = val;
            }
        }
        if(count == 1)
        {
            m_there_is_only_one_possible_value = true;
        }
    }

    void SudokuGrid::getPossibleValuesForEasyWins(int r, int c)
    {
        std::fill(m_possible_values, m_possible_values + 9, true);

        // check the row
        for(int col = 0; col < 9; ++col)
        {
            int val = get(r, col);
            if(val != 0)
            {
                m_possible_values[val - 1] = false;
            }
        }

        // check the column
        for(int row = 0; row < 9; ++row)
        {
            int val = get(row, c);
            if(val != 0)
            {
                m_possible_values[val - 1] = false;
            }
        }

        // check the square
        int start_row = (r / 3) * 3;
        int start_col = (c / 3) * 3;
        for(int dr = 0; dr < 3; ++dr)
        {
            for(int dc = 0; dc < 3; ++dc)
            {
                int val = get(start_row + dr, start_col + dc);
                if(val != 0)
                {
                    m_possible_values[val - 1] = false;
                }
            }
        }
    }

} // namespace Sudoku