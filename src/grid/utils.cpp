#include "sudoku_grid.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>



namespace Sudoku
{
    std::ostream& bold_on(std::ostream& os)
    {
        return os << "\e[1m";
    }

    std::ostream& bold_off(std::ostream& os)
    {
        return os << "\e[0m";
    }

    void SudokuGrid::putValuesIntoArray(int* outputArr) const
    {
        std::copy(m_grid, m_grid + N_GRID_CELLS, outputArr);
    }

    void SudokuGrid::print() const
    {
        for(int r = 0; r < 9; ++r)
        {
            for(int c = 0; c < 9; ++c)
            {
                std::cout << get(r, c) << " ";
            }
            std::cout << std::endl;
        }
    }

    void SudokuGrid::printWithGroundTruth(int* groundTruth) const
    {
    
        /*
        
        Print the grid with ground truth values. Values that were part of the original puzzle (non-zero in groundTruth)
        are printed in bold.
        There are also pipes to indicate 3x3 subgrid boundaries for better readability.
        */
        auto makeOutputBold = []() { std::cout << bold_on; };
        auto makeOutputNotBold = []() { std::cout << bold_off; };
        std::cout << std::endl;
        for(int r = 0; r < 9; ++r)
        {
            for(int c = 0; c < 9; ++c)
            {
                if(groundTruth[r * GRID_ROW_SIZE + c] != 0)
                    makeOutputBold();
                std::cout << get(r, c);
                makeOutputNotBold();
                if(c == 2 || c == 5)
                    std::cout << " | ";
                else
                    std::cout << " ";
            }
            std::cout << std::endl;
            if(r == 2 || r == 5)
            {
                std::cout << "---------------------" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void SudokuGrid::clearSeen()
    {
        std::fill(m_seen, m_seen + 9, false);
    }

    void SudokuGrid::copyFrom(const SudokuGrid& other)
    {
        other.putValuesIntoArray(m_grid);
    }
} // namespace Sudoku
