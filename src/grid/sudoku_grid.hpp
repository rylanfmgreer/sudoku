
#ifndef _SUDOKU_GRID_HPP_
#define _SUDOKU_GRID_HPP_

#include <vector>
#include <memory>
#include "helper_structs/helper_structs.hpp"

namespace Sudoku
{


    const int N_GRID_CELLS = 81;
    const int GRID_ROW_SIZE = 9;
    typedef short int IndexInt;
    typedef short int ValueInt;
    typedef ValueInt* Grid;


    class SudokuGrid
    {

        public:
        /*
            Default constructor for SudokuGrid
            Does not initialize grid values.
        */
        SudokuGrid();

        /*
            Copy constructor for SudokuGrid
            Copies the grid values and helper structs from another SudokuGrid.
        */
        SudokuGrid(const SudokuGrid& other);

        /*
            Destructor for SudokuGrid
            Cleans up allocated memory (81 ValueInts as well as some workspace structs).
        */
        ~SudokuGrid();

        /*
            Solves the Sudoku grid using deduction and backtracking.
            If the grid is already solved, it returns immediately.
        */
        void solve();

        /*
            Solves the Sudoku grid after first checking if the grid is valid.
            If the grid is invalid, it returns immediately without attempting to solve.
        */
        void solveWithValidityCheckFirst();

        /*
            Check if the Sudoku grid is completely solved and valid.
            A grid is considered solved if there are no empty cells (zeros)
            and all rows, columns, and 3x3 squares are legal.
        */
        bool isSolved() const;

        /*
            Print the Sudoku grid to a very basic text format.
        */
        void print() const;

        /*
            Print the Sudoku grid with ground truth values highlighted.
            The formatting is also improved for readability.
        */
        void printWithGroundTruth(Grid groundTruth) const;

        /*
            Get the value at the specified row and column.
            :param r: Row index (0-8)
            :param c: Column index (0-8)
            :return: Value at the specified cell (0-9)
        */
        inline ValueInt& get(IndexInt r, IndexInt c) const { return m_grid[r * GRID_ROW_SIZE + c]; }
        inline ValueInt& operator()(IndexInt r, IndexInt c) const { return get(r, c); }

        /*
            Set the value at the specified row and column.
            :param r: Row index (0-8)
            :param c: Column index (0-8)
            :param val: Value to set at the specified cell (0-9)
        */
        inline void set(IndexInt r, IndexInt c, ValueInt val) { m_grid[r * GRID_ROW_SIZE + c] = val; }

        /*
            Take the current grid values and put them into the provided output array.
            The output array must have space for at least N_GRID_CELLS (81) ValueInt elements.

            :param outputArr: Pointer to an array of ValueInt to hold the grid values.
        */
        void putValuesIntoArray(ValueInt* outputArr) const;

        private:
        Grid m_grid;

        /*
            Helpers for solving -- return the possible next states
        */
        std::vector<SudokuGrid> getNextGrids(IndexInt r=-1, IndexInt c=-1) const;
        std::vector<SudokuGrid> helperGetNextGrids(IndexInt r=-1, IndexInt c=-1) const;
        /*
            Helper to find the next empty cell in the grid.
        */
        void findNextEmptyCell() const;

        /*
            Helper to take values from another grid and copy them into this grid.
            :param other: The SudokuGrid to copy values from.
        */
        void copyFrom(const SudokuGrid& other);

        /*
            Check if the specified row is legal (contains no duplicates).
            :param r: Row index (0-8)
            :return: True if the row is legal, false otherwise.
        */
        bool thisRowIsLegal(IndexInt r) const;

        /*
            Check if all rows in the grid are legal.
            :return: True if all rows are legal, false otherwise.
        */
        bool allRowsAreLegal() const;

        /*
            Check if the specified column is legal (contains no duplicates).
            :param c: Column index (0-8)
            :return: True if the column is legal, false otherwise.
        */
        bool thisColumnIsLegal(IndexInt c) const;

        /*
            Check if all columns in the grid are legal.
            :return: True if all columns are legal, false otherwise.
        */
        bool allColumnsAreLegal() const;

        /*
            Check if the 3x3 square containing the cell at (r, c) is legal.
            :param r: Row index (0-8)
            :param c: Column index (0-8)
            :return: True if the square is legal, false otherwise.
        */
        bool thisSquareIsLegal(IndexInt r, IndexInt c) const;

        /*
            Check if all 3x3 squares in the grid are legal.
            :return: True if all squares are legal, false otherwise.
        */
        bool allSquaresAreLegal() const;

        /*
            Check if the entire grid is legal (all rows, columns, and squares are legal).
            :return: True if the grid is legal, false otherwise.
        */
        bool totalGridIsLegal() const;

        /*
            Check if the entire grid is legal (all rows, columns, and squares are legal).
            :return: True if the grid is legal, false otherwise.
        */
        bool thisGridIsLegal(IndexInt r, IndexInt c) const;

        /*
            Clear the 'seen' array in the possible values helper.
        */
        inline void clearSeen() const { std::fill(m_possible_values_helper.seen, m_possible_values_helper.seen + 9, false); }

        /*
            Clear the 'possible_values' array in the possible values helper.
        */
        inline void clearPossibleValues() const { std::fill(m_possible_values_helper.possible_values, m_possible_values_helper.possible_values + 9, true); }

        /*
            Check if there are no zero entries in the grid.
            :return: True if there are no zeros, false otherwise.
        */
        bool noZeroEntriesInThisGrid() const;

        /*
            Determine if there is only one possible value for the current cell
            and save that value in the possible values helper.
        */
        void determineIfThereIsASinglePossibleValueAndSaveIt();


        /*
            Apply all deductive reasoning algorithms to the grid.
        */
        void applyAllDeductiveReasoning();

        /*
            Apply a very simple deduction technique: filling in cells
            that have only one possible value and assigning that value to the cell.
            As simple as this is, it can solve many easy Sudoku puzzles outright
            and can significantly reduce the search space in branches for harder puzzles.
        */
        void easyWins();
        /*
            Get the possible values for the cell at (r, c) for easy wins.
            Updates the possible values helper accordingly.

            :param r: Row index (0-8)
            :param c: Column index (0-8)
        */
        void getPossibleValuesForEasyWins(IndexInt r, IndexInt c) const;

        /*
            Workspace helpers for solving
        */
        mutable SudokuGridNextEmptyCellHelper m_next_empty_cell_helper;
        mutable SudokuGridPossibleValuesHelper m_possible_values_helper;
    };

} // namespace Sudoku
#endif //_SUDOKU_GRID_HPP_