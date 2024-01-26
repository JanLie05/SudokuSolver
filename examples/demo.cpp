#include <sudokuSolver/Solver.hpp>

int main(){
    sudokuSolver::Solver solver ("examples/sudoku.txt");
    solver.printGrid();
    solver.solve();
    solver.printGrid();
    return 0;
}