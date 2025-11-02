#include "solver_wrapper.hpp"
#include <chrono>
#include <iostream>
#include "../grid_reader/grid_reader.hpp"

namespace Sudoku
{
    long int currentTimeInMilliseconds()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        return now_ms.time_since_epoch().count();
    }

    bool solveSingleGrid(SudokuGrid& grid, bool verbose)
    {
        long int start_time = currentTimeInMilliseconds();
        ValueInt groundTruthArr[N_GRID_CELLS];
        grid.putValuesIntoArray(groundTruthArr);

        grid.solve();
        long int end_time = currentTimeInMilliseconds();
        if (verbose)
        {
            std::cout << "Grid solved: " << grid.isSolved() << std::endl;
            std::cout << "Time taken: " << (end_time - start_time) << " milliseconds" << std::endl;
            std::cout << "Grid state:" << std::endl;
            grid.printWithGroundTruth(groundTruthArr);
        }
        return grid.isSolved();
    }

    int solveVectorOfGrids(std::vector<SudokuGrid>& grids, bool verbose)
    {
        int solved_count = 0;
        long int total_start_time = currentTimeInMilliseconds();
        for(auto& grid : grids)
            solved_count += solveSingleGrid(grid, verbose);
        long int total_end_time = currentTimeInMilliseconds();
        if (verbose)
        {
            std::cout << "Total grids solved: " << solved_count << " out of " << grids.size() << std::endl;
            std::cout << "Total time taken: " << (total_end_time - total_start_time) << " milliseconds" << std::endl;
        }
        return solved_count;
    }

    int solveGridsFromFile(const char* filename, bool verbose)
    {
        std::vector<SudokuGrid> grids = readGridsFromFile(filename);
        return solveVectorOfGrids(grids, verbose);
    }
} // namespace Sudoku
