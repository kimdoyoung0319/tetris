#ifndef SCREEN_H
#define SCREEN_H

#include <locale.h>
#include <ncursesw/ncurses.h>
#include "board.h"

using std::vector;

constexpr int MAIN_WINDOW_WIDTH = 22;
constexpr int MAIN_WINDOW_HEIGHT = 23;
constexpr int MAIN_WINDOW_POS_X = 1;
constexpr int MAIN_WINDOW_POS_Y = 1;
constexpr int BLACK_AND_WHITE = 1;

class Screen {
    private:
        WINDOW * main_window;
        void draw_square(const Coordinate &) const;
        void erase_square(const Coordinate &) const;
        inline void refresh_main_window() const;
        friend class Game;
    public:
        Screen();
        ~Screen();
        void update_main_window(const Board &) const;
};

#endif
