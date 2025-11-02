#ifndef _OTHER_UTILS_SUDOKU_GRID_HPP
#define _OTHER_UTILS_SUDOKU_GRID_HPP
#include <algorithm>
#include <string>
#include <iostream>

namespace Sudoku
{
    /*
        String consts (including colour codes for terminal output)
    */
    const std::string boldBlueTextCode = "\e[1;34m";
    const std::string normalTextCode = "\e[0m";
    const std::string lineSeparator = "-------------------------\n";
    const std::string lineBreak = "\n";

    /*
        Set the text mode to ground truth (bold blue).
    */
    void setGroundTruthTextMode();
    
    /*
        Set the text mode back to normal.
    */
    void setNormalTextMode();
} // namespace Sudoku
#endif