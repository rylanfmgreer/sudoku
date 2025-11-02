#ifndef SRC_GRID_HELPER_STRUCTS_HELPER_STRUCTS_HPP_
#define SRC_GRID_HELPER_STRUCTS_HELPER_STRUCTS_HPP_

#include "../../data_types.hpp"

namespace Sudoku
{
    typedef short int IndexInt;
    typedef short int ValueInt;

    struct SudokuGridNextEmptyCellHelper
    {
        IndexInt next_empty_row;
        IndexInt next_empty_col;
        SudokuGridNextEmptyCellHelper(const SudokuGridNextEmptyCellHelper& other)
        : next_empty_row(other.next_empty_row), next_empty_col(other.next_empty_col) {}
        SudokuGridNextEmptyCellHelper() : next_empty_row(-1), next_empty_col(-1) {}

    };

    struct SudokuGridPossibleValuesHelper
    {
        bool seen[9];
        bool possible_values[9];
        bool there_is_only_one_possible_value;
        ValueInt single_possible_value;
        SudokuGridPossibleValuesHelper(const SudokuGridPossibleValuesHelper& other)
        : there_is_only_one_possible_value(other.there_is_only_one_possible_value),
          single_possible_value(other.single_possible_value)
        {}

        SudokuGridPossibleValuesHelper()
        : there_is_only_one_possible_value(false), single_possible_value(-1)
        {}
    };
} // namespace Sudoku

#endif // SRC_GRID_HELPER_STRUCTS_HELPER_STRUCTS_HPP_