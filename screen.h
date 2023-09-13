#ifndef SCREEN_H
#define SCREEN_H

#include <ncursesw/ncurses.h>

#include "board.h"

class Screen {
    private:
        //Adding 2 to the size of the board to make a room for drawing box.
        //Multiplying 2 to the size of the row of the board
        //because the characters are half-sized.
        const int main_window_width = 2 * 10 + 2;
        const int main_window_height = 21 + 2;

        const Coordinate main_window_position{1, 1};

        enum ColorPair {WHITE_BLACK_PAIR, YELLOW_BLACK_PAIR};

        WINDOW * main_window;

        void draw_square_normal(const Coordinate &) const;
        void draw_square_highlighted(const Coordinate &) const;
        void erase_square(const Coordinate &) const;

        void refresh_main_window() const;

        friend class Game;

    public:
        Screen();
        ~Screen();

        void update_main_window(const Board &, const Block &) const;
        void update_main_window(const Board &) const;
};

#endif
