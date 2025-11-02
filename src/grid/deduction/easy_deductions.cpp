#include "../sudoku_grid.hpp"

namespace Sudoku
{
    void SudokuGrid::easyWins()
    {
        /*
        This function fills in easy wins for the Sudoku grid by looking for cells
        that have only one possible value and assigning that value to the cell.
        */
        bool progress = true;
        while(progress)
        {
            progress = false;
            for(int r = 0; r < 9; ++r)
            {
                for(int c = 0; c < 9; ++c)
                {
                    if(get(r, c)== 0)
                    {
                        getPossibleValuesForEasyWins(r, c);
                        determineIfThereIsASinglePossibleValueAndSaveIt();
                        if(m_there_is_only_one_possible_value)
                        {
                            set(r, c, m_single_possible_value);
                            progress = true;
                        }
                    }
                }
            }
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
    
} // namespace Sudoku
