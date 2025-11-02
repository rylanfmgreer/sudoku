
#ifndef _SUDOKU_GRID_HPP_
#define _SUDOKU_GRID_HPP_

#include <vector>
#include <memory>

namespace Sudoku
{
    struct SudokuGridNextEmptyCellHelper
    {
        std::size_t next_empty_row;
        std::size_t next_empty_col;
        SudokuGridNextEmptyCellHelper(const SudokuGridNextEmptyCellHelper& other)
        : next_empty_row(other.next_empty_row), next_empty_col(other.next_empty_col) {}
        SudokuGridNextEmptyCellHelper() : next_empty_row(-1), next_empty_col(-1) {}

    };

    struct SudokuGridPossibleValuesHelper
    {
        bool seen[9];
        bool possible_values[9];
        bool there_is_only_one_possible_value;
        int single_possible_value;
        SudokuGridPossibleValuesHelper(const SudokuGridPossibleValuesHelper& other)
        : there_is_only_one_possible_value(other.there_is_only_one_possible_value),
          single_possible_value(other.single_possible_value)
        {
            std::copy(other.seen, other.seen + 9, seen);
            std::copy(other.possible_values, other.possible_values + 9, possible_values);
        }

        SudokuGridPossibleValuesHelper()
        : there_is_only_one_possible_value(false), single_possible_value(-1)
        {
            std::fill(seen, seen + 9, false);
            std::fill(possible_values, possible_values + 9, true);
        }
    };

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
        inline void clearSeen() const { std::fill(m_possible_values_helper->seen, m_possible_values_helper->seen + 9, false); }
        inline void clearPossibleValues() const { std::fill(m_possible_values_helper->possible_values, m_possible_values_helper->possible_values + 9, true); }
        bool noZeroEntriesInThisGrid() const;

        void determineIfThereIsASinglePossibleValueAndSaveIt();


        // deduction algorithms
        // currently only the simple one is implemented, but more can be added later
        void applyAllDeductiveReasoning();
        void easyWins();
        void getPossibleValuesForEasyWins(IndexInt r, IndexInt c) const;

        // we consider a function const even if it modifies these data in these helpers
        std::shared_ptr<SudokuGridNextEmptyCellHelper> m_next_empty_cell_helper;
        std::shared_ptr<SudokuGridPossibleValuesHelper> m_possible_values_helper;
    };

} // namespace Sudoku
#endif //_SUDOKU_GRID_HPP_