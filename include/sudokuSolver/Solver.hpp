#pragma once

#include <sudokuSolver/Cell.hpp>
#include <array>
#include <string>

namespace sudokuSolver {
    class Solver {
        public:
            //constructor, takes filePath to tthe to be solved sudoku 
            Solver(std::string filePath);

            //solves the sudoku, returns true if succesful
            bool solve();

             //prints the current state of the 9x9 grid of the sudoku 
            void printGrid() const;

        private:
             //the sudoku grid
            std::array<std::array<Cell, 9>, 9> grid;

            //finds the cell with the fewest options and returns its row and column as an array
            std::array<int, 2> findCellWithFewestOptions() const;

            //either removes or adds the value at grid[row][column] to the corresponding row, column or subgrid 
            void updateGridOptions(int row, int column, bool remove);

            //returns true if every cell is filled
            bool isGridFilled() const;

           
    };
}