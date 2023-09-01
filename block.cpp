#include "block.h"
#include <iostream>

const Coordinate Coordinate::operator+(const Coordinate & other) {
    return Coordinate{x + other.x, y + other.y};
}

const Coordinate Coordinate::operator-(const Coordinate & other) {
    return Coordinate{x - other.x, y - other.y};
}

Block::Block(BlockType block_type) : position(INITIAL_POS), 
                                    shape(blocktype_to_shape(block_type)),
                                    prev_position(INITIAL_POS),
                                    prev_shape(shape) {
}

const vector<vector<bool>> Block::blocktype_to_shape(BlockType block_type) {
    switch(block_type) {
        case BLOCK_I: return SHAPE_I;
        case BLOCK_J: return SHAPE_J;
        case BLOCK_L: return SHAPE_L;
        case BLOCK_O: return SHAPE_O;
        case BLOCK_S: return SHAPE_S;
        case BLOCK_T: return SHAPE_T;
        case BLOCK_Z: return SHAPE_Z;
        default: throw std::invalid_argument("Wrong block type to blocktype_to_shape()");
    }
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
    prev_shape = shape;
    vector<vector<bool>> new_shape(BLOCK_SIDE, vector<bool>(BLOCK_SIDE, false));
    Coordinate new_position, relative_position;
    for(int i = 0; i < BLOCK_SIDE; i++) {
        for(int j = 0; j < BLOCK_SIDE; j++) {
            if(shape[i][j]){
                relative_position = Coordinate{j, i} - ORIGIN;
                new_position = Coordinate{-relative_position.y, relative_position.x} + ORIGIN;
                new_shape[new_position.y][new_position.x] = shape[i][j];
            }
        }
    }
    shape = new_shape;
    
    return;
}

void Block::rotate_ccw() {
    prev_shape = shape;
    vector<vector<bool>> new_shape(BLOCK_SIDE, vector<bool>(BLOCK_SIDE, false));
    Coordinate new_position, relative_position;
    for(int i = 0; i < BLOCK_SIDE; i++) {
        for(int j = 0; j < BLOCK_SIDE; j++) {
            if(shape[i][j]){
                relative_position = Coordinate{j, i} - ORIGIN;
                new_position = Coordinate{relative_position.y, -relative_position.x} + ORIGIN;
                new_shape[new_position.y][new_position.x] = shape[i][j];
            }
        }
    }
    shape = new_shape;
    
    return;
}

void Block::undo() {
    std::swap<Coordinate>(position, prev_position);
    std::swap<vector<vector<bool>>>(shape, prev_shape);
}

const Coordinate & Block::get_position() const {
    return position;
}

const bool Block::is_filled(const Coordinate & position) const {
    return shape[position.y][position.x];
}
