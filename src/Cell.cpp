#include <sudokuSolver/Cell.hpp>

namespace sudokuSolver {
    Cell::Cell() : value(0), options({1, 2, 3, 4, 5, 6, 7, 8, 9}){
    }

    void Cell::removeOption(int option) {
        int toBeRemoved = -1;
        for(int i = 0; i < options.size(); i++) {
            if(options[i] == option) {
                toBeRemoved = i;
                break;
            }
        }
        if(toBeRemoved == -1) {
            return;
        }
        options.erase(options.begin() + toBeRemoved);
    }
    
    void Cell::addOption(int option) {
        if(option < 0 or option > 10) {
            return;
        }
        removeOption(option); //try to remove option to make sure its not added twice 
        options.push_back(option);
    }
    
    void Cell::fill(int fillValue) {
        if(fillValue < 0 or fillValue > 10) { 
            return;
        }
        value = fillValue;
        removeOption(fillValue);
    }

    void Cell::setNotFilled() {
        value = 0;
    }
    
    int Cell::getNumberOfOptions() const {
        return options.size();
    }

    int Cell::getFirstOption() const {
        if(options.empty()) {
            return 0;
        }
        return options[0];
    }
    
    int Cell::getValue() const {
        return value;
    }

    bool Cell::isFilled() const {
        return value != 0;
    }
}