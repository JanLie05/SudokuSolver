#pragma once

#include <vector>


namespace sudokuSolver {
    class Cell {
        public:
            Cell();

            //SETTERS
            void removeOption(int option);
            void addOption(int option);   
            void fill(int fillValue);
            void setNotFilled();

            //GETTERS
            int getNumberOfOptions() const;
            int getFirstOption() const;
            int getValue() const;
            //returns true if current value is not 0
            bool isFilled() const;
 
        private:
            //current value of the cell, 0 if empty
            int value;
            //options that cell could be filled with
            std::vector<int> options;
    };
}
