#include "solver_wrapper.hpp"
#include <chrono>
#include <iostream>
#include "../grid_reader/grid_reader.hpp"

namespace Sudoku
{
    double current_time()
    {
        return static_cast<double>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    bool solve_single_grid(SudokuGrid& grid, bool verbose)
    {
        double start_time = current_time();
        grid.solve();
        double end_time = current_time();
        if (verbose)
        {
            std::cout << "Grid solved: " << grid.is_solved() << std::endl;
            std::cout << "Time taken: " << (end_time - start_time) << " microseconds" << std::endl;
            std::cout << "Grid state:" << std::endl;
            grid.print();
        }
        return grid.is_solved();
    }

    int solve_vector_of_grids(std::vector<SudokuGrid>& grids, bool verbose)
    {
        int solved_count = 0;
        double total_start_time = current_time();
        for(auto& grid : grids)
            solved_count += solve_single_grid(grid, verbose);
        double total_end_time = current_time();
        if (verbose)
        {
            std::cout << "Total grids solved: " << solved_count << " out of " << grids.size() << std::endl;
            std::cout << "Total time taken: " << (total_end_time - total_start_time) << " microseconds" << std::endl;
        }
        return solved_count;
    }

    int solve_grids_from_file(const char* filename, bool verbose)
    {
        std::vector<SudokuGrid> grids = read_grids_from_file(filename);
        return solve_vector_of_grids(grids, verbose);
    }
} // namespace Sudoku
