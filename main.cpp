#include<cstdlib>
#include<iostream>
#include <iomanip>

#include "src/table.h"
#include "src/snake.h"


int main() {

    Table<int> t(20, 10);
    for(size_t i = 0; i < t.size(); ++i) {
        t.at(i) = i;
    }

    for(auto val: t) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    for(auto val: t.line(2)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    for(auto val: t.col(2)) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    for(auto line: t.lines()) {
        for(auto value: line) {
            std::cout << std::setw(5) << value << " ";
        }
        std::cout << std::endl;
    }
        std::cout << std::endl;


    for(auto col: t.columns()) {
        for(auto value: col) {
            std::cout << std::setw(5) << value << " ";
        }
        std::cout << std::endl;
    }
        std::cout << std::endl;

    Snake snake(40, 40);
    for(size_t i = 0; i < 100; ++i) {
        std::cout << snake << std::endl;
        snake.right();
        std::cout << snake << std::endl;
        snake.down();
    }

    return EXIT_SUCCESS;
}