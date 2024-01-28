#include <sudokuSolver/Solver.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace sudokuSolver {

    Solver::Solver(std::string filePath) {
        
        //open the file and save content in vector
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
          throw ;  
        }

        //fill grid with either a empty cell or a prefilled cell
        for(int r = 0; r < grid.size(); r++) {
            for(int c = 0; c < grid[r].size(); c++) {
                Cell cell;
                if(lines[r].at(c) != '0') { //if cell is prefilled
                    cell.fill(lines[r].at(c) - '0');
                }
                grid[r][c] = cell;
            }
        }

        //remove options of cells in row, column or subgrid of prefilled cells
        for(int r = 0; r < grid.size(); r++) {
            for(int c = 0; c < grid[r].size(); c++) {
                if(grid[r][c].getValue() == 0) {
                    continue;
                } else {
                    updateGridOptions(r, c, true);
                }
            }
        }
    }

    bool Solver::solve() {
        if(isGridFilled()) {
            return true;
        }

        std::array<int, 2> cellPosition = findCellWithFewestOptions();
        Cell& optimalCell =  grid[cellPosition[0]][cellPosition[1]];

        for(int i = 0; i < optimalCell.getNumberOfOptions(); i++) { //try every possible option until grid is filled
            optimalCell.fill(optimalCell.getFirstOption());
            updateGridOptions(cellPosition[0], cellPosition[1], true);
            if(solve()) { //if recursive call returns true, grid is filled
                return true;
            } else { //else current value is wrong, so reset
                updateGridOptions(cellPosition[0], cellPosition[1], false);
                optimalCell.setNotFilled();
            }
        }
        return false; // Sudoku can't be solved
    }

    void Solver::updateGridOptions(int row, int column, bool remove) {
        if(row < 0 or row > 9 or column < 0 or column > 9) {
            return;
        }
       
        //row and column
        for(int i = 0; i < grid.size(); i++) {
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
                      
        //subgrid
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

    std::array<int, 2> Solver::findCellWithFewestOptions() const{
        int fewestOptions = 10;
        std::array<int,2> positionOfCell = {-1, -1};

        for(int r = 0; r < grid.size(); r++) {
            for(int c = 0; c < grid[r].size(); c++) {
                if(!(grid[r][c].isFilled()) and grid[r][c].getNumberOfOptions() < fewestOptions) { //if cell is not filled and has fewer options
                    fewestOptions = grid[r][c].getNumberOfOptions();
                    positionOfCell[0] = r;
                    positionOfCell[1] = c;
                }
            }
        }
        return positionOfCell;
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