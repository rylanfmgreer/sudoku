#include "grid_reader.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

namespace Sudoku
{
    std::vector<SudokuGrid> read_grids_from_file(const char* filename)
    {
        std::vector<SudokuGrid> grids;
        std::ifstream infile(filename);
        if(!infile)
            throw std::runtime_error(std::string("Could not open file: ") + filename);

        std::string line;
        while(std::getline(infile, line))
        {
            // skip empty lines
            auto first_non_ws = line.find_first_not_of(" \t\r\n");
            if(first_non_ws == std::string::npos)
                continue;

            // look for a "Grid" header
            if(line.compare(first_non_ws, 4, "Grid") != 0)
                continue;

            SudokuGrid grid;
            for(int r = 0; r < 9; ++r)
            {
                if(!std::getline(infile, line))
                    throw std::runtime_error("Unexpected end of file while reading grid lines");

                // trim leading/trailing whitespace
                auto start = line.find_first_not_of(" \t\r\n");
                auto end = line.find_last_not_of(" \t\r\n");
                if(start == std::string::npos || end == std::string::npos || end - start + 1 < 9)
                    throw std::runtime_error("Invalid grid line format: '" + line + "'");

                std::string digits = line.substr(start, end - start + 1);
                if(digits.size() < 9)
                    throw std::runtime_error("Grid line too short: '" + line + "'");

                for(int c = 0; c < 9; ++c)
                {
                    char ch = digits[c];
                    if(!std::isdigit(static_cast<unsigned char>(ch)))
                        throw std::runtime_error("Non-digit character in grid line");
                    grid.set(r, c, ch - '0');
                }
            }
            grids.push_back(grid);
        }
        return grids;
    }
} // namespace _Problem96