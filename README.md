# Sudoku Solver

Sudoku grids must be input using the format given by grids.txt.
The output given is the grids solved as well as the time taken.

## Description of algorithm:
The code uses a mix of deduction logic and a depth-first search.
I intend to try more deduction techniques, but I have found that the solver is fairly fast as it stands
(1-5ms per puzzle on my machine.) Partly this is down to some seemingly minor optimizations on some routine calculations.

## To compile (on my machine):
For my own reference, I am using this command to compile:
g++ -std=c++17 -stdlib=libc++ -g main.cpp  $(find src -type f -iregex ".*\.cpp") -o solve
I am no expert in compilers so of course this may be of no use to you.

## To run (on my machine)
Run in a command prompt.
If no filename is supplied, it will look for a file in the same path as it's being run called "grids.txt".
You can also supply a filename eg by running
> ./solve grids.txt

## Reqired file input:
Please see grids.txt as an example -- in general:
1. The filename must have the word "Grid" before every grid
2. Grids must be input as 9 rows of 9 digits, with 0s for blank cells
