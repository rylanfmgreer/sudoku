
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
        bool is_solved();
        void print() const;

        // accessors
        int& get(int r, int c) const;
        int& operator()(int r, int c) const { return get(r, c); }
        void set(int r, int c, int val);


        private:
        grid m_grid;
        std::vector<SudokuGrid> get_next_grids(int r=-1, int c=-1);
        std::vector<SudokuGrid> _get_next_grids(int r=-1, int c=-1);


        int m_next_empty_row;
        int m_next_empty_col;
        void find_next_empty_cell();

        void copy_from(const SudokuGrid& other);

        // helpers for checking
        bool m_seen[9];
        bool this_row_is_ok(int r);
        bool all_rows_are_ok();
        bool this_column_is_ok(int c);
        bool all_columns_are_ok();
        bool this_square_is_ok(int r, int c);
        bool all_squares_are_ok();
        bool everything_is_ok(int r, int c);
        bool grid_is_ok();
        void clear_seen();
        bool no_zero_entries() const;

        void determine_if_there_is_a_single_possible_value();
        bool m_there_is_only_one_possible_value;
        int m_single_possible_value;

        // deduction algorithms
        // currently only the simple one is implemented, but more can be added later
        bool m_possible_values[9];
        void fill_in_easy_wins();
        void get_possible_values(int r, int c);
    };
} // namespace Sudoku
#endif //_SUDOKU_GRID_HPP_