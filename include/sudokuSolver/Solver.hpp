#pragma once

#include <array>
#include <set>
#include <functional>
#include <sudokuSolver/Cell.hpp>

namespace sudokuSolver {
    class Solver {
        public:
            Solver();
            std::array<int, 2> findOptimalCell();
            void updateCellOptions(int row, int column);
            void printGrid() const;
        private:
            std::array<std::array<Cell, 9>, 9> grid;
    };
}