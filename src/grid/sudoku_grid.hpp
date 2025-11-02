
#ifndef _SUDOKU_GRID_HPP_
#define _SUDOKU_GRID_HPP_

#include <vector>

namespace Sudoku
{
    const int N_GRID_CELLS = 81;
    const int GRID_ROW_SIZE = 9;
    typedef int* grid;

    class SudokuGrid
    {

        public:
        // Constructors
        SudokuGrid();
        SudokuGrid(const SudokuGrid& other);
        ~SudokuGrid();

        // key function to solve the sudoku
        void solve();
        bool isSolved();
        void print() const;

        // accessors
        int& get(int r, int c) const;
        int& operator()(int r, int c) const { return get(r, c); }
        void set(int r, int c, int val);


        private:
        grid m_grid;
        std::vector<SudokuGrid> getNextGrids(int r=-1, int c=-1);
        std::vector<SudokuGrid> helperGetNextGrids(int r=-1, int c=-1);


        int m_next_empty_row;
        int m_next_empty_col;
        void findNextEmptyCell();

        void copyFrom(const SudokuGrid& other);

        // helpers for checking
        bool m_seen[9];
        bool thisRowIsLegal(int r);
        bool allRowsAreLegal();
        bool thisColumnIsLegal(int c);
        bool allColumnsAreLegal();
        bool thisSquareIsLegal(int r, int c);
        bool allSquaresAreLegal();
        bool thisGridIsLegal(int r, int c);
        bool totalGridIsLegal();
        void clearSeen();
        bool noZeroEntriesInThisGrid() const;

        void determineIfThereIsASinglePossibleValueAndSaveIt();
        bool m_there_is_only_one_possible_value;
        int m_single_possible_value;

        // deduction algorithms
        // currently only the simple one is implemented, but more can be added later
        bool m_possible_values[9];
        void easyWins();
        void getPossibleValuesForEasyWins(int r, int c);
    };
} // namespace Sudoku
#endif //_SUDOKU_GRID_HPP_