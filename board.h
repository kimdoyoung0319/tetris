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
        void update_board(const Block &);
        void delete_last_line();
        void fix_block();
        bool is_block_valid(const Block &) const;
        bool is_last_line_full() const;
        bool is_filled(const Coordinate &) const;
        bool is_filled_dynamic(const Coordinate &) const;
        bool is_filled_static(const Coordinate &) const;
};

#endif
