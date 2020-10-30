void Snake::left() {
    next_state = State::LEFT;
}

void Snake::right() {
    next_state = State::RIGHT;
}

void Snake::up() {
    next_state = State::UP;
}

void Snake::down() {
    next_state = State::DOWN;
}

void Snake::move() {
    switch (current_state = next_state) {
        case State::LEFT:
            _move_left();
            break;
        case State::RIGHT:
            _move_right();
            break;
        case State::UP:
            _move_up();
            break;
        case State::DOWN:
            _move_down();
            break;
    }
}