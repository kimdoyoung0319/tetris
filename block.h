#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <stdexcept>

using std::vector;

struct Coordinate {
    int x, y;
    const Coordinate operator+(const Coordinate &);
    const Coordinate operator-(const Coordinate &);
};

enum BlockType {
    BLOCK_I,
    BLOCK_J,
    BLOCK_L,
    BLOCK_O,
    BLOCK_S,
    BLOCK_T,
    BLOCK_Z,
};


constexpr int BLOCK_SIDE = 4;
constexpr int INITIAL_POS_X = 3;
constexpr int INITIAL_POS_Y = 0;
constexpr int ORIGIN_X = 2;
constexpr int ORIGIN_Y = 1;
constexpr Coordinate INITIAL_POS{INITIAL_POS_X, INITIAL_POS_Y};
constexpr Coordinate ORIGIN{ORIGIN_X, ORIGIN_Y};

const vector<vector<bool>> SHAPE_I = {{0, 0, 0, 0}, 
                                      {1, 1, 1, 1}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_J = {{0, 1, 0, 0}, 
                                      {0, 1, 1, 1}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_L = {{0, 0, 0, 1}, 
                                      {0, 1, 1, 1}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_O = {{0, 1, 1, 0}, 
                                      {0, 1, 1, 0}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_S = {{0, 1, 0, 0}, 
                                      {0, 1, 1, 0}, 
                                      {0, 0, 1, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_T = {{0, 0, 1, 0}, 
                                      {0, 1, 1, 1}, 
                                      {0, 0, 0, 0}, 
                                      {0, 0, 0, 0}};

const vector<vector<bool>> SHAPE_Z = {{0, 0, 1, 0}, 
                                      {0, 1, 1, 0}, 
                                      {0, 1, 0, 0}, 
                                      {0, 0, 0, 0}};

class Block {
    private:
        Coordinate position, prev_position;
        vector<vector<bool>> shape, prev_shape;
        const vector<vector<bool>> blocktype_to_shape(BlockType);
    public:
        Block(BlockType);
        void move_right();
        void move_left();
        void move_down();
        void rotate_cw();
        void rotate_ccw();
        void undo();
        const Coordinate & get_position() const;
        const bool is_filled(const Coordinate &) const;
};

#endif
