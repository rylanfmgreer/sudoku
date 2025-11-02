#ifndef _DATA_TYPES_HPP_
#define _DATA_TYPES_HPP_

namespace Sudoku
{
    typedef short int IndexInt;
    typedef short int ValueInt;
    typedef ValueInt* Grid;
    const IndexInt N_GRID_CELLS = 81;
    const IndexInt GRID_ROW_SIZE = 9;

} // namespace Sudoku

#endif