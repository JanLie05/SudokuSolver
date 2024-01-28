#include <sudokuSolver/Solver.hpp>
#include <iostream>

int main(int argc, char *argv[]){
    try {
    if(argc != 2 ) {
        throw std::invalid_argument("No or to many arguments"); 
    }
    } catch (const std::invalid_argument& e) {
        std::cout<<e.what()<<std::endl;
    }

    try {
        sudokuSolver::Solver solver (argv[1]);
        solver.solve();
        solver.printGrid();
    } catch (const std::invalid_argument& e) {
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}