#pragma once

#include <vector>


namespace sudokuSolver {
    class Cell {
        public:
            Cell();
            void addOption(int option);
            bool isFilled() const;
            int getNumberOfOptions() const;
            int getValue() const;
            bool removeOption(int option);
            void fill(int fillValue);
            int getFirstOption() const;
            void setNotFilled();
        private:
            int value;
            std::vector<int> options;
            bool filled;
    };
}
