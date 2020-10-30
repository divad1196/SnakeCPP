#ifndef SNAKE_H
#define SNAKE_H

#include <cstdlib>
#include <iostream>

#include "table.h"

class Snake {
    public:
        using PlayBoard = Table<size_t>;
        using Coord = std::pair<size_t, size_t>;

        class Iterator {
            public:
                Iterator(const PlayBoard* board, size_t index): _board(board), _index(index) {}
                Iterator(const PlayBoard& board, size_t index): Iterator(&board, index) {}

                Iterator& operator++() {
                    _index = _board->at(_index);
                    return *this;
                }

                Iterator operator++(int) {
                    Iterator it(_board, _index);
                    _index = _board->at(_index);
                    return it;
                }

                bool operator==(const Iterator& it) const {
                    return _index == it._index;
                }

                bool operator!=(const Iterator& it) const {
                    return _index != it._index;
                }

                Coord operator* () const
                {
                    return _board->coord(_index);
                }

            private:
                size_t _index;
                const PlayBoard* _board;
        };

        static const size_t NONE;
        static const size_t APPLE;
        static const size_t HEAD_VALUE;

        Snake(size_t line, size_t row);

        void left();
        void right();
        void up();
        void down();

        Iterator begin() const {
            return Iterator(_board, tail_idx);
        }

        Iterator end() const {
            return Iterator(_board, HEAD_VALUE);
        }

    private:

        void move();

        void _move(int dx, int dy);
        
        size_t tail_idx;
        int head_x;
        int head_y;

        static const int SNAKE_PART;

        PlayBoard _board;

};

std::ostream& operator<<(std::ostream& stream, const Snake& snake);

#endif // SNAKE_H