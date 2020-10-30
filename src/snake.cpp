#include "snake.h"


const size_t Snake::NONE = -1;
const size_t Snake::APPLE = -2;
const size_t Snake::HEAD_VALUE = -3;

Snake::Snake(size_t line, size_t row): _board(line, row, Snake::NONE) {
    size_t initial_size = 3;
    // Check initial_size > 0
    // Check initial_size < row
    tail_idx = 0;
    head_y = 0;
    head_x = initial_size - 1;
    for(size_t index = 0; index < initial_size - 1; ++index) {
        _board.at(index) = index + 1;
    }
    _board.at(head_x) = HEAD_VALUE;
}

void Snake::left() {
    _move(-1, 0);
}

void Snake::right() {
    _move(1, 0);
}

void Snake::up() {
    _move(0, -1);
}

void Snake::down() {
    _move(0, 1);
}

void Snake::_move(int dx, int dy) {
    size_t head_idx = _board.index(head_x, head_y); 
    size_t next_index = _board.index(head_x + dx, head_y + dy);
    std::cout << head_idx << std::endl;
    std::cout << next_index << std::endl;
    if(_board.at(next_index) != APPLE)
        _board.at(tail_idx) = NONE;
    // else ...

    _board.at(head_idx) = next_index;
    _board.at(next_index) = HEAD_VALUE;
}


std::ostream& operator<<(std::ostream& stream, const Snake& snake) {
    for(const auto coord: snake) {
        stream << '(' << coord.first << ", " << coord.second << ") ";
    }
    return stream;
}
