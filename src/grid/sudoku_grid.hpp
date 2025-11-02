
#ifndef _SUDOKU_GRID_HPP_
#define _SUDOKU_GRID_HPP_

#include <vector>
#include <memory>
#include "helper_structs/helper_structs.hpp"
#include "../data_types.hpp"

namespace Sudoku
{
    const IndexInt N_GRID_CELLS = 81;
    const IndexInt GRID_ROW_SIZE = 9;
    typedef ValueInt* Grid;


    class SudokuGrid
    {

        public:
        /**
         * @brief Default constructor for SudokuGrid
         * 
         * Does not initialize grid values.
         */
        SudokuGrid();

        /**
         * @brief Copy constructor for SudokuGrid
         * 
         * Copies the grid values and helper structs from another SudokuGrid.
         * 
         * @param other The SudokuGrid to copy from
         */
        SudokuGrid(const SudokuGrid& other);

        /**
         * @brief Destructor for SudokuGrid
         * 
         * Cleans up allocated memory (81 ValueInts as well as some workspace structs).
         */
        ~SudokuGrid();

        /**
         * @brief Solves the Sudoku grid using deduction and backtracking
         * 
         * If the grid is already solved, it returns immediately.
         */
        void solve();

        /**
         * @brief Solves the Sudoku grid after first checking if the grid is valid
         * 
         * If the grid is invalid, it returns immediately without attempting to solve.
         */
        void solveWithValidityCheckFirst();

        /**
         * @brief Check if the Sudoku grid is completely solved and valid
         * 
         * A grid is considered solved if there are no empty cells (zeros)
         * and all rows, columns, and 3x3 squares are legal.
         * 
         * @return True if the grid is solved, false otherwise
         */
        bool isSolved() const;

        /**
         * @brief Print the Sudoku grid to a very basic text format
         */
        void print() const;

        /**
         * @brief Print the Sudoku grid with ground truth values highlighted
         * 
         * The formatting is also improved for readability.
         * 
         * @param groundTruth Pointer to the ground truth grid values
         */
        void printWithGroundTruth(Grid groundTruth) const;

        /**
         * @brief Get the value at the specified row and column
         * 
         * @param r Row index (0-8)
         * @param c Column index (0-8)
         * @return Reference to the value at the specified cell (0-9)
         */
        inline ValueInt& get(IndexInt r, IndexInt c) const { return m_grid[r * GRID_ROW_SIZE + c]; }
        
        /**
         * @brief Operator overload for accessing grid values
         * 
         * @param r Row index (0-8)
         * @param c Column index (0-8)
         * @return Reference to the value at the specified cell (0-9)
         */
        inline ValueInt& operator()(IndexInt r, IndexInt c) const { return get(r, c); }

        /**
         * @brief Set the value at the specified row and column
         * 
         * @param r Row index (0-8)
         * @param c Column index (0-8)
         * @param val Value to set at the specified cell (0-9)
         */
        inline void set(IndexInt r, IndexInt c, ValueInt val) { m_grid[r * GRID_ROW_SIZE + c] = val; }

        /**
         * @brief Take the current grid values and put them into the provided output array
         * 
         * The output array must have space for at least N_GRID_CELLS (81) ValueInt elements.
         *
         * @param outputArr Pointer to an array of ValueInt to hold the grid values
         */
        void putValuesIntoArray(ValueInt* outputArr) const;

        private:
        Grid m_grid; ///< The 9x9 Sudoku grid stored as a flat array

        /**
         * @brief Get possible next states by trying values in a cell
         * 
         * @param r Row index (0-8), or -1 to auto-find next empty cell
         * @param c Column index (0-8), or -1 to auto-find next empty cell
         * @return Vector of possible next grid states
         */
        std::vector<SudokuGrid> getNextGrids(IndexInt r=-1, IndexInt c=-1) const;
        
        /**
         * @brief Helper function to generate next grids for a specific cell
         * 
         * @param r Row index (0-8)
         * @param c Column index (0-8)
         * @return Vector of possible next grid states
         */
        std::vector<SudokuGrid> helperGetNextGrids(IndexInt r=-1, IndexInt c=-1) const;
        
        /**
         * @brief Find the next empty cell in the grid
         * 
         * Updates m_next_empty_cell_helper with the coordinates of the next empty cell.
         */
        void findNextEmptyCell() const;

        /**
         * @brief Copy values from another grid into this grid
         * 
         * @param other The SudokuGrid to copy values from
         */
        void copyFrom(const SudokuGrid& other);

        /**
         * @brief Check if the specified row is legal (contains no duplicates)
         * 
         * @param r Row index (0-8)
         * @return True if the row is legal, false otherwise
         */
        bool thisRowIsLegal(IndexInt r) const;

        /**
         * @brief Check if all rows in the grid are legal
         * 
         * @return True if all rows are legal, false otherwise
         */
        bool allRowsAreLegal() const;

        /**
         * @brief Check if the specified column is legal (contains no duplicates)
         * 
         * @param c Column index (0-8)
         * @return True if the column is legal, false otherwise
         */
        bool thisColumnIsLegal(IndexInt c) const;

        /**
         * @brief Check if all columns in the grid are legal
         * 
         * @return True if all columns are legal, false otherwise
         */
        bool allColumnsAreLegal() const;

        /**
         * @brief Check if the 3x3 square containing the cell at (r, c) is legal
         * 
         * @param r Row index (0-8)
         * @param c Column index (0-8)
         * @return True if the square is legal, false otherwise
         */
        bool thisSquareIsLegal(IndexInt r, IndexInt c) const;

        /**
         * @brief Check if all 3x3 squares in the grid are legal
         * 
         * @return True if all squares are legal, false otherwise
         */
        bool allSquaresAreLegal() const;

        /**
         * @brief Check if the entire grid is legal (all rows, columns, and squares are legal)
         * 
         * @return True if the grid is legal, false otherwise
         */
        bool totalGridIsLegal() const;

        /**
         * @brief Check if the grid is legal around a specific cell
         * 
         * Checks the row, column, and 3x3 square containing the specified cell.
         * 
         * @param r Row index (0-8)
         * @param c Column index (0-8)
         * @return True if the grid is legal around this cell, false otherwise
         */
        bool thisGridIsLegal(IndexInt r, IndexInt c) const;

        /**
         * @brief Clear the 'seen' array in the possible values helper
         */
        inline void clearSeen() const { std::fill(m_possible_values_helper.seen, m_possible_values_helper.seen + 9, false); }

        /**
         * @brief Clear the 'possible_values' array in the possible values helper
         */
        inline void clearPossibleValues() const { std::fill(m_possible_values_helper.possible_values, m_possible_values_helper.possible_values + 9, true); }

        /**
         * @brief Check if there are no zero entries in the grid
         * 
         * @return True if there are no zeros, false otherwise
         */
        bool allGridEntriesAreFilledIn() const;

        /**
         * @brief Determine if there is only one possible value for the current cell
         * 
         * Updates the possible values helper with the result and saves the value if unique.
         */
        void determineIfThereIsASinglePossibleValueAndSaveIt();


        /**
         * @brief Apply all deductive reasoning algorithms to the grid
         * 
         * Currently only applies the easyWins algorithm, but more can be added.
         */
        void applyAllDeductiveReasoning();

        /**
         * @brief Apply simple deduction: fill cells with only one possible value
         * 
         * This technique fills in cells that have only one possible value and assigns
         * that value to the cell. As simple as this is, it can solve many easy Sudoku
         * puzzles outright and can significantly reduce the search space in branches
         * for harder puzzles.
         */
        void easyWins();
        
        /**
         * @brief Get the possible values for the cell at (r, c) for easy wins
         * 
         * Updates the possible values helper accordingly by checking the row, column,
         * and 3x3 square containing the cell.
         *
         * @param r Row index (0-8)
         * @param c Column index (0-8)
         */
        void getPossibleValuesForEasyWins(IndexInt r, IndexInt c) const;

        mutable SudokuGridNextEmptyCellHelper m_next_empty_cell_helper; ///< Workspace helper for finding next empty cell
        mutable SudokuGridPossibleValuesHelper m_possible_values_helper; ///< Workspace helper for tracking possible values
    };

} // namespace Sudoku
#endif //_SUDOKU_GRID_HPP_