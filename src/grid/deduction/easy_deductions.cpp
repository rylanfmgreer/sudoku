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
    
} // namespace Sudoku
