#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "block.h"

using std::vector;
using std::cout;
using std::endl;

constexpr int LENGTH_ROW = 10;
constexpr int LENGTH_COL = 21;

class Board {
    private:
        vector<vector<bool>> board_static, board_dynamic;
    public:
        Board();
        void print_board() const;
        void update_board(const Block &);
        void delete_last_line();
        bool check_block(const Block &) const;
        bool check_last_line() const;
};

#endif