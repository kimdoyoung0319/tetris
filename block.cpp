#include "block.h"

Coordinate Coordinate::operator+(const Coordinate & other) {
    return Coordinate{x + other.x, y + other.y};
}

Coordinate Coordinate::operator-(const Coordinate & other) {
    return Coordinate{x - other.x, y - other.y};
}

Coordinate Coordinate::operator*(int other) {
    return Coordinate{x * other, y * other};
}

Coordinate Coordinate::operator/(int other) {
    return Coordinate{x / other, y / other};
}

inline void Block::save_state() {
    prev_position = position;
    prev_shape = shape;
    
    return;
}

void Block::move_right() {
    save_state();
    
    position.x++;
}

void Block::move_left() {
    save_state();
    
    position.x--;
}

void Block::move_down() {
    save_state();
    
    position.y++;
}

void Block::rotate() {
    save_state();

    const Coordinate origin{1, 1};

    matrix_t new_shape(col_size, row_t(row_size, false));
    Coordinate new_coordinate;

    for(int i = 0; i < col_size; i++) {
        for(int j = 0; j < row_size; j++) {
            if(shape[i][j]) {
                new_coordinate = Coordinate{j, i} - origin;
                new_coordinate = Coordinate{-new_coordinate.y, new_coordinate.x} + origin;
                new_shape[new_coordinate.y][new_coordinate.x] = true;
            }
        }
    }

    shape = new_shape;

    return;
}

//Notice that the undo() method 'undo's only one modification of the block;
//which means that, if you call undo() twice in a row,
//the block will only return to its beginning state.
void Block::undo() {
    std::swap<Coordinate>(position, prev_position);
    std::swap<matrix_t>(shape, prev_shape);

    return;
}

const Coordinate & Block::get_position() const {
    return position;
}

const bool Block::is_filled(const Coordinate & coordinate) const {
    return shape[coordinate.y][coordinate.x];
}

void IBlock::rotate() {
    save_state();

    constexpr Coordinate origin{3, 3};

    matrix_t new_shape(col_size, row_t(row_size, false));
    Coordinate new_coordinate;

    for(int i = 0; i < col_size; i++) {
        for(int j = 0; j < row_size; j++) {
            if(shape[i][j]) {
                //Because the rotational origin of the I block is in between squares,
                //I doubled up the coordinates of a square,
                //so that the newly inserted squares would represent a line between squares.
                new_coordinate = Coordinate{j, i} * 2 - origin;
                new_coordinate = Coordinate{-new_coordinate.y, new_coordinate.x} + origin;
                new_coordinate = new_coordinate / 2;
                new_shape[new_coordinate.y][new_coordinate.x] = true;
            }
        }
    }

    shape = new_shape;

    return;
}

void OBlock::rotate() {
    //The O block doesn't change its shape when the block rotates!
    save_state();

    return;
}
