#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
#include "block.h"

class Board {
    public:
        const int row_size = 10;
        const int col_size = 21;

    private:
        matrix_t shape;

        bool is_coordinate_out_of_bound(const Coordinate &) const;

    public:
        Board();

        void erase_full_rows();
        void fix(const Block &);

        bool is_last_row_full() const;
        bool is_valid(const Block &) const;
        bool is_filled(const Coordinate &) const;
};

#endif
