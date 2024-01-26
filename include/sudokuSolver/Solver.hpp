#pragma once

#include <array>
#include <set>
#include <functional>
#include <string>
#include <sudokuSolver/Cell.hpp>

namespace sudokuSolver {
    class Solver {
        public:
            Solver(std::string filePath);
            void printGrid() const;
            bool solve();
        private:
            std::array<int, 2> findOptimalCell();
            void updateCellOptions(int row, int column, bool remove);
            bool isGridFilled() const;
            std::array<std::array<Cell, 9>, 9> grid;
    };
}