#ifndef _BLOCK_H
#define _BLOCK_H

#include <vector>

using std::vector;

struct Coordinate {
    int x, y;
};

const int BLOCK_SIDE = 4;
const int INITIAL_POS_X = 3;
const int INITIAL_POS_Y = 0;
const Coordinate INITIAL_POS{INITIAL_POS_X, INITIAL_POS_Y};

class Block {
    private:
        Coordinate position;
        vector<vector<bool>> shape;
    public:
        Block();
        Block(const vector<vector<bool>> &);
        void move_right();
        void move_left();
        void move_down();
        void rotate_cw();
        void rotate_ccw();
        const Coordinate get_position() const;
        const vector<vector<bool>> get_shape() const;
};

#endif