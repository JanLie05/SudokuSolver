#include <sudokuSolver/Cell.hpp>

namespace sudokuSolver {
    Cell::Cell() : value(0), filled(false), options({1, 2, 3, 4, 5, 6, 7, 8, 9}){
    }

    bool Cell::removeOption(int option) {
        int toBeRemoved = -1;
        for(int i = 0; i < options.size(); i++) {
            if(options[i] == option) {
                toBeRemoved = i;
                break;
            }
        }
        if(toBeRemoved == -1) {
            return false;
        }
        options.erase(options.begin() + toBeRemoved);
        return true;
    }
    
    void Cell::addOption(int option) {
        removeOption(option); //try to remove option to make sure its not added twice 
        options.push_back(option);
    }
    
    bool Cell::isFilled() const {
        return filled;
    }
    
    int Cell::getNumberOfOptions() const {
        return options.size();
    }
    
    int Cell::getValue() const {
        return value;
    }

    void Cell::setNotFilled() {
        filled = false;
        value = 0;
    }

    void Cell::fill(int fillValue) {
        if(fillValue < 0 or fillValue > 10) {
            return;
        }
        value = fillValue;
        filled = true;
        removeOption(fillValue);
    }

    int Cell::getFirstOption() const {
        if(options.empty()) {
            return -1;
        }
        return options[0];
    }
}