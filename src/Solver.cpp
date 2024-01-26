#include <sudokuSolver/Solver.hpp>
#include <iostream>
#include <fstream>

namespace sudokuSolver {
    Solver::Solver(std::string filePath) {
        std::ifstream file;
        file.open(filePath);
        std::vector<std::string> lines;
        std::string currentLine;

        if(file.is_open()) {
            int lineNum = 0;
            while(file.good()) {
                std::getline(file, currentLine);
                if(lineNum > 9 or currentLine.size() > 9 or !std::all_of(currentLine.begin(), currentLine.end(), [](char c) -> bool { return std::isdigit(c); })) {
                    std::cout<<"Invalid file!"<<std::endl;
                    return;
                }
                lines.push_back(currentLine);
            }
        } else {
          std::cout<<"Invalid filepath!"<<std::endl;
          return;  
        }

        for(int r = 0; r < grid.size(); r++) {
            for(int c = 0; c < grid[r].size(); c++) {
                Cell cell;
                if(lines[r].at(c) != '0') {
                    cell.fill(lines[r].at(c) - '0');
                }
                grid[r][c] = cell;
            }
        }

        for(int r = 0; r < grid.size(); r++) {
            for(int c = 0; c < grid[r].size(); c++) {
                if(grid[r][c].getValue() == 0) {
                    continue;
                } else {
                    updateCellOptions(r, c, true);
                }
            }
        }
    }

    bool Solver::solve() {
        if(isGridFilled()) {
            return true;
        }
        std::array<int, 2> cellPosition = findOptimalCell();
        Cell& optimalCell =  grid[cellPosition[0]][cellPosition[1]];
        for(int i = 0; i < optimalCell.getNumberOfOptions(); i++) {
            optimalCell.fill(optimalCell.getFirstOption());
            updateCellOptions(cellPosition[0], cellPosition[1], true);
            if(solve()) {
                return true;
            } else {
                updateCellOptions(cellPosition[0], cellPosition[1], false);
                optimalCell.setNotFilled();
            }
        }
        return false; // Sudoku can't be solved
    }

    void Solver::updateCellOptions(int row, int column, bool remove) {
        //rows and columns
        for(int i = 0; i < 9; i++) {
            if (remove) {
                if(i != column) { //skip element itself
                    grid[row][i].removeOption(grid[row][column].getValue());
                }
                if (i != row) {
                    grid[i][column].removeOption(grid[row][column].getValue());
                }
            } else {
                if (i != column) {
                    grid[row][i].addOption(grid[row][column].getValue());
                }
                if (i != row) {
                    grid[i][column].addOption(grid[row][column].getValue());
                }
            }
        }
                      
        //subgrids
        for(int r = ((row/3)*3); r < (((row/3)*3)+3); r++) {
            for(int c = ((column/3)*3); c < (((column/3)*3)+3); c++) {
                if(r != row and c != column) {
                    if (remove) {
                        grid[r][c].removeOption(grid[row][column].getValue());
                    } else {
                        grid[r][c].addOption(grid[row][column].getValue());
                    }
                }
            }
        }

    }

    std::array<int, 2> Solver::findOptimalCell() {
        int fewestOptions = 10;
        std::array<int,2> positionOfOptimalCell = {-1, -1};
        for(int r = 0; r < grid.size(); r++) {
            for(int c = 0; c < grid[r].size(); c++) {
                if(!(grid[r][c].isFilled()) and grid[r][c].getNumberOfOptions() < fewestOptions) {
                    fewestOptions = grid[r][c].getNumberOfOptions();
                    positionOfOptimalCell[0] = r;
                    positionOfOptimalCell[1] = c;
                }
            }
        }
        return positionOfOptimalCell;
    }

    bool Solver::isGridFilled() const{
        for(const std::array<Cell,9>& arr : grid) {
            for(const Cell& cell : arr) {
                if(!cell.isFilled()) {
                    return false;
                }
            }
        }
        return true;
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
                std::cout<<"   "<<(grid[r][c].getValue() == 0 ? " " : std::to_string(grid[r][c].getValue()));
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