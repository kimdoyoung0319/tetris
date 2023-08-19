#include <iostream>
#include <vector>

struct Coordinate {
    int x, y;
};

using std::vector;

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
        Coordinate get_position();
        const vector<vector<bool>> get_shape() const;
};

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

Coordinate Block::get_position() {
    return position;
}

const vector<vector<bool>> Block::get_shape() const {
    return shape;
}

int main(void){
    vector<vector<bool>> shape = {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
    };
    Block block(shape);
    std::cout << "position = (" << block.get_position().x << ", " << block.get_position().y << ")" << std::endl;;
    block.move_right();
    std::cout << "position = (" << block.get_position().x << ", " << block.get_position().y << ")" << std::endl;;
    block.move_left();
    std::cout << "position = (" << block.get_position().x << ", " << block.get_position().y << ")" << std::endl;;
    block.move_down();
    std::cout << "position = (" << block.get_position().x << ", " << block.get_position().y << ")" << std::endl;;
    
    vector<vector<bool>> got_shape = block.get_shape();
    for(int i = 0; i < BLOCK_SIDE; i++){
        for(int j = 0; j < BLOCK_SIDE; j++)
            std::cout << (got_shape[i][j] ? "■" : "□");
        std::cout << std::endl;
    }
    
    return 0;
}