#include "../sudoku_grid.hpp"
namespace Sudoku
{
    void SudokuGrid::applyAllDeductiveReasoning()
    {
        // Apply all known deduction techniques to the Grid
        easyWins();
    }
} // namespace Sudoku
