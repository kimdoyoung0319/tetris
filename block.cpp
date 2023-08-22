#include "block.h"
#include <iostream>

const Coordinate Coordinate::operator+(const Coordinate & other) {
    return Coordinate{x + other.x, y + other.y};
}

const Coordinate Coordinate::operator-(const Coordinate & other) {
    return Coordinate{x - other.x, y - other.y};
}

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

const vector<vector<bool>> & Block::get_shape() const {
    return shape;
}