#ifndef _OTHER_UTILS_SUDOKU_GRID_HPP
#define _OTHER_UTILS_SUDOKU_GRID_HPP
#include <algorithm>
#include <string>
#include <iostream>

namespace Sudoku
{
    const std::string boldBlueTextCode = "\e[1;34m";
    const std::string normalTextCode = "\e[0m";
    const std::string lineSeparator = "-------------------------\n";
    const std::string lineBreak = "\n";
    std::ostream& groundTruthTextMode(std::ostream& os);
    std::ostream& normalText(std::ostream& os);
} // namespace Sudoku
#endif