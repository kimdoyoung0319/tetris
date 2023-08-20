#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using std::vector;

struct Coordinate {
    int x, y;
};

constexpr int BLOCK_SIDE = 4;
constexpr int INITIAL_POS_X = 3;
constexpr int INITIAL_POS_Y = 0;
constexpr Coordinate INITIAL_POS{INITIAL_POS_X, INITIAL_POS_Y};

const vector<vector<bool>> SHAPE_I = {{0, 1, 0, 0}, 
                                      {0, 1, 0, 0}, 
                                      {0, 1, 0, 0}, 
                                      {0, 1, 0, 0}};

const vector<vector<bool>> SHAPE_J = {{0, 0, 1, 0}, 
                                      {0, 0, 1, 0}, 
                                      {0, 1, 1, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_L = {{0, 1, 0, 0}, 
                                      {0, 1, 0, 0}, 
                                      {0, 1, 1, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_O = {{0, 1, 1, 0}, 
                                      {0, 1, 1, 0}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_S = {{0, 1, 1, 0}, 
                                      {1, 1, 0, 0}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_T = {{0, 1, 1, 1}, 
                                      {0, 0, 1, 0}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_Z = {{0, 1, 1, 0}, 
                                      {0, 0, 1, 1}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

class Block {
    private:
        Coordinate position, prev_position;
        vector<vector<bool>> shape, prev_shape;
    public:
        Block();
        Block(const vector<vector<bool>> &);
        void move_right();
        void move_left();
        void move_down();
        void rotate_cw();
        void rotate_ccw();
        void undo();
        const Coordinate & get_position() const;
        const vector<vector<bool>> & get_shape() const;
};

#endif