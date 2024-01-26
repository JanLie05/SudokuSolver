#include <sudokuSolver/Solver.hpp>
#include <iostream>

namespace sudokuSolver {
    Solver::Solver() {
        for(int i; i < grid.size(); i++) {
            for(int j; j < grid[i].size(); j++) {
                Cell c;
                grid[i][j] = c;
            }
        }

        for(int i = 0; i < 81; i++) { 
            std::array<int, 2> cellPosition = findOptimalCell();
            grid[cellPosition[0]][cellPosition[1]].fill(grid[cellPosition[0]][cellPosition[1]].getFirstOption());
            updateCellOptions(cellPosition[0], cellPosition[1]);
        }

    }

    void Solver::updateCellOptions(int row, int column) {
        //rows and columns
        for(int i = 0; i < 9; i++) {
            grid[row][i].removeOption(grid[row][column].getValue());
            grid[i][column].removeOption(grid[row][column].getValue());
        }
        //subgrids
        for(int r = ((row/3)*3); r < (((row/3)*3)+3); r++) {
            for(int c = ((column/3)*3); c < (((column/3)*3)+3); c++) {
                grid[r][c].removeOption(grid[row][column].getValue());
            }
        }

    }

    std::array<int, 2> Solver::findOptimalCell() {
        int fewestOptions = 10;
        std::array<int,2> positionOfOptimalCell= {-1, -1};
        for(int r = 0; r < grid.size(); r++) {
            for(int c = 0; c < grid[r].size(); c++) {
                if(!grid[r][c].isFilled() and grid[r][c].getNumberOfOptions() < fewestOptions) {
                    fewestOptions = grid[r][c].getNumberOfOptions();
                    positionOfOptimalCell[0] = r;
                    positionOfOptimalCell[1] = c;
                }
            }
        }
        return positionOfOptimalCell;
    }

    void Solver::printGrid() const{
        std::string seperator(77, '-' );
        std::string padding = "||";
        for(int i = 0; i < 9; i++) {
            padding += (i % 3 == 2 ? "       ||" : "       |");
        }

        std::cout<<seperator<<std::endl<<seperator<<std::endl;
        for(int r = 0; r < grid.size(); r++) {
            std::cout<<padding<<std::endl;
            std::cout<<"||";
            for(int c = 0; c < grid[r].size(); c++) {
                std::cout<<"   "<<(grid[r][c].getValue() == -1 ? " " : std::to_string(grid[r][c].getValue()));
                std::cout<< (c % 3 == 2 ? "   ||" : "   |");
            }
            std::cout<<std::endl;
            std::cout<<padding<<std::endl;
            std::cout<<seperator<<std::endl;
            if(r % 3 == 2) {
                std::cout<<seperator<<std::endl;
            }
        }
    }




}