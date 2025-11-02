#ifndef _SOLVER_WRAPPER_HPP_
#define _SOLVER_WRAPPER_HPP_
#include "../grid_reader/grid_reader.hpp"
#include "../grid/sudoku_grid.hpp"

namespace Sudoku
{
    /*
        Solve a single sudoku grid. If verbose is true, print out information about the solving process.
        Returns true if the grid was solved successfully, false otherwise.

        :param grid: The SudokuGrid to be solved.
        :param verbose: Whether to print verbose output.
        :return: True if solved, false otherwise.
    */
    bool solveSingleGrid(SudokuGrid& grid, bool verbose=true);

    /*
        Solve a vector of sudoku grids. If verbose is true, print out information about the solving process.
        Returns the number of grids solved successfully.

        :param grids: The vector of SudokuGrid to be solved.
        :param verbose: Whether to print verbose output.
        :return: Number of grids solved.
    */
    int solveVectorOfGrids(std::vector<SudokuGrid>& grids, bool verbose=true);

    /*
        Read sudoku grids from a file and solve them. If verbose is true, print out information about the solving process.
        Returns the number of grids solved successfully.

        :param filename: The name of the file containing sudoku grids.
        :param verbose: Whether to print verbose output.
        :return: Number of grids solved.
    */
    int solveGridsFromFile(const char* filename, bool verbose=true);

    /*
        Get the current time in milliseconds since epoch.

        :return: Current time in milliseconds.
    */
    long int currentTimeInMilliseconds();

} // namespace Sudoku


#endif