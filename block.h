#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

struct Coordinate {
    int x, y;

    Coordinate operator+(const Coordinate &);
    Coordinate operator-(const Coordinate &);
    Coordinate operator*(int);
    Coordinate operator/(int);
};

enum BlockType {
    BLOCK_I, BLOCK_J, BLOCK_L, BLOCK_O, BLOCK_S, BLOCK_T, BLOCK_Z
};


typedef std::vector<std::vector<bool>> matrix_t;
typedef std::vector<bool> row_t;

constexpr Coordinate INITIAL_POSITION{3, 0};

static const matrix_t SHAPE_I = {{0, 0, 0, 0},
                                 {1, 1, 1, 1},
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0}};

static const matrix_t SHAPE_J = {{1, 0, 0},
                                 {1, 1, 1},
                                 {0, 0, 0}};

static const matrix_t SHAPE_L = {{0, 0, 1},
                                 {1, 1, 1},
                                 {0, 0, 0}};

static const matrix_t SHAPE_O = {{0, 1, 1, 0},
                                 {0, 1, 1, 0},
                                 {0, 0, 0, 0}};

static const matrix_t SHAPE_S = {{0, 1, 1},
                                 {1, 1, 0},
                                 {0, 0, 0}};

static const matrix_t SHAPE_T = {{0, 1, 0},
                                 {1, 1, 1},
                                 {0, 0, 0}};

static const matrix_t SHAPE_Z = {{1, 1, 0},
                                 {0, 1, 1},
                                 {0, 0, 0}};

class Block {
    private:
        Coordinate position = INITIAL_POSITION;
        Coordinate prev_position = INITIAL_POSITION;

    protected:
        Block(matrix_t initial_shape)
            : shape(initial_shape), prev_shape(initial_shape),
              row_size(initial_shape[0].size()), col_size(initial_shape.size()) {
        }

        matrix_t shape;
        matrix_t prev_shape;

        inline void save_state();

    public:
        void move_right();
        void move_left();
        void move_down();
        virtual void rotate();

        void undo();
        
        const Coordinate & get_position() const;
        const bool is_filled(const Coordinate &) const;

        const int row_size;
        const int col_size;
};

class IBlock : public Block {
    public:
        IBlock() : Block(SHAPE_I) {
        }

        void rotate() override;
};

class JBlock : public Block {
    public:
        JBlock() : Block(SHAPE_J) {
        }
};

class LBlock : public Block {
    public:
        LBlock() : Block(SHAPE_L) {
        }
};

class OBlock : public Block {
    public:
        OBlock() : Block(SHAPE_O) {
        }

        void rotate() override;
};

class SBlock : public Block {
    public:
        SBlock() : Block(SHAPE_S) {
        }
};

class TBlock : public Block {
    public:
        TBlock() : Block(SHAPE_T) {
        }
};

class ZBlock : public Block {
    public:
        ZBlock() : Block(SHAPE_Z) {
        }
};

#endif
