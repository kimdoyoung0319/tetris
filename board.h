#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include "block.h"

using std::vector;

const int LENGTH_ROW= 10;
const int LENGTH_COL= 21;

class Board{
    private:
        vector<vector<bool>> board;
    public:
        Board();
        void print_board() const;
        void update_board(const Block &);
        void delete_line();
        bool check_position(const Block &) const; 
        bool check_end(const Block &) const;
        bool check_line() const;
};

#endif