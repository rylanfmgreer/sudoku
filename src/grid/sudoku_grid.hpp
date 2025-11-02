
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
        // Constructors
        SudokuGrid();
        SudokuGrid(const SudokuGrid& other);
        ~SudokuGrid();

        // key function to solve the sudoku
        void solve();
        void solveWithValidityCheckFirst();
        bool isSolved() const;
        void print() const;
        void printWithGroundTruth(Grid groundTruth) const;

        // accessors
        inline ValueInt& get(IndexInt r, IndexInt c) const { return m_grid[r * GRID_ROW_SIZE + c]; }
        inline ValueInt& operator()(IndexInt r, IndexInt c) const { return get(r, c); }
        inline void set(IndexInt r, IndexInt c, ValueInt val) { m_grid[r * GRID_ROW_SIZE + c] = val; }

        // utilities that may be useful externally
        void putValuesIntoArray(ValueInt* outputArr) const;

        private:
        Grid m_grid;
        std::vector<SudokuGrid> getNextGrids(IndexInt r=-1, IndexInt c=-1) const;
        std::vector<SudokuGrid> helperGetNextGrids(IndexInt r=-1, IndexInt c=-1) const;
        void findNextEmptyCell() const;
        void copyFrom(const SudokuGrid& other);

        // helpers for checking
        bool thisRowIsLegal(IndexInt r) const;
        bool allRowsAreLegal() const;
        bool thisColumnIsLegal(IndexInt c) const;
        bool allColumnsAreLegal() const;
        bool thisSquareIsLegal(IndexInt r, IndexInt c) const;
        bool allSquaresAreLegal() const;
        bool totalGridIsLegal() const;
        bool thisGridIsLegal(IndexInt r, IndexInt c) const;
        inline void clearSeen() const { std::fill(m_possible_values_helper.seen, m_possible_values_helper.seen + 9, false); }
        inline void clearPossibleValues() const { std::fill(m_possible_values_helper.possible_values, m_possible_values_helper.possible_values + 9, true); }
        bool noZeroEntriesInThisGrid() const;

        void determineIfThereIsASinglePossibleValueAndSaveIt();


        // deduction algorithms
        // currently only the simple one is implemented, but more can be added later
        void applyAllDeductiveReasoning();
        void easyWins();
        void getPossibleValuesForEasyWins(IndexInt r, IndexInt c) const;

        // mutable allows these workspace variables to be modified even in const functions
        mutable SudokuGridNextEmptyCellHelper m_next_empty_cell_helper;
        mutable SudokuGridPossibleValuesHelper m_possible_values_helper;
    };

} // namespace Sudoku
#endif //_SUDOKU_GRID_HPP_