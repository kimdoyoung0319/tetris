#include "block.h"

Block::Block() : position(INITIAL_POS), 
                 shape(BLOCK_SIDE, vector<bool>(BLOCK_SIDE, false)),
                 prev_position(INITIAL_POS),
                 prev_shape(BLOCK_SIDE, vector<bool>(BLOCK_SIDE, false)) {
}

Block::Block(const vector<vector<bool>> & shape) : position(INITIAL_POS), 
                                                   shape(shape),
                                                   prev_position(INITIAL_POS),
                                                   prev_shape(shape) {
}

void Block::move_right() {
    prev_position = position;
    position.x++;
}

void Block::move_left() {
    prev_position = position;
    position.x--;
}

void Block::move_down() {
    prev_position = position;
    position.y++;
}

void Block::rotate_cw() {
}

void Block::undo() {
    Coordinate temp_position = position;
    position = prev_position;
    prev_position = temp_position;
    
    vector<vector<bool>> temp_shape = shape;
    shape = prev_shape;
    prev_shape = temp_shape;
}

const Coordinate & Block::get_position() const {
    return position;
}

const vector<vector<bool>> & Block::get_shape() const {
    return shape;
}