# Sudoku Solver

Sudoku grids must be input using the format given by grids.txt.
The output given is the grids solved as well as the time taken.

For my own reference, I am using this command to compile:
g++ -std=c++17 -stdlib=libc++ -g main.cpp  $(find src -type f -iregex ".*\.cpp") -o a

The code uses a mix of deduction logic and a depth-first search. I intend to implement more deduction logic later; right now, the code is fast enough for my purposes using only the deductions I show.