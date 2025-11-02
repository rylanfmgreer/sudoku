#include "sudoku_grid.hpp"
#include "other_utils.hpp"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>


namespace Sudoku
{
    std::ostream& groundTruthTextMode(std::ostream& os)
    {
        return os << boldBlueTextCode;
    }

    std::ostream& normalText(std::ostream& os)
    {
        return os << normalTextCode;
    }

    void SudokuGrid::putValuesIntoArray(Grid outputArr) const
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

    void SudokuGrid::printWithGroundTruth(ValueInt* groundTruth) const
    {
    
        /*
        
        Print the grid with ground truth values. Values that were part of the original puzzle (non-zero in groundTruth)
        are printed in bold.
        There are also pipes to indicate 3x3 subgrid boundaries for better readability.
        */
        auto makeOutputBold = []() { std::cout << groundTruthTextMode; };
        auto makeOutputNotBold = []() { std::cout << normalText; };
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
                std::cout << lineSeparator << lineBreak;
            }
        }
        std::cout << lineBreak;
    }

    void SudokuGrid::clearSeen() const
    {
        std::fill(m_possible_values_helper->seen,
            m_possible_values_helper->seen + 9, false);
    }

    void SudokuGrid::copyFrom(const SudokuGrid& other)
    {
        other.putValuesIntoArray(m_grid);
    }
} // namespace Sudoku
