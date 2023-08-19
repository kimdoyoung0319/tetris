#include "block.h"

Block::Block() : position(INITIAL_POS), shape(BLOCK_SIDE, vector<bool>(BLOCK_SIDE, false)) {
}

Block::Block(const vector<vector<bool>> &shape) : position(INITIAL_POS), shape(shape) {
}

void Block::move_right() {
    position.x++;
}

void Block::move_left() {
    position.x--;
}

void Block::move_down() {
    position.y++;
}

const Coordinate Block::get_position() const {
    return position;
}

const vector<vector<bool>> Block::get_shape() const {
    return shape;
}