#ifndef SCREEN_H
#define SCREEN_H

#include <ncursesw/ncurses.h>
#include <string>

#include "board.h"

class Screen {
    private:
        //Adding 2 to the size of the board to make a room for drawing box.
        //Multiplying 2 to the size of the row of the board
        //because the characters are half-sized.
        const int main_window_width = 2 * 10 + 2;
        const int main_window_height = 21 + 2;
        const Coordinate main_window_position{1, 1};

        const int score_window_width = 12;
        const int score_window_height = 3;
        const Coordinate score_window_position{24, 1};

        const int message_window_width = 12;
        const int message_window_height = 3;
        const Coordinate message_window_position{24, 4};

        enum ColorPair {WHITE_BLACK_PAIR, YELLOW_BLACK_PAIR};

        WINDOW * main_window;
        WINDOW * score_window;
        WINDOW * message_window;

        void draw_square_normal(const Coordinate &) const;
        void draw_square_highlighted(const Coordinate &) const;
        void erase_square(const Coordinate &) const;

        void refresh_window(WINDOW *) const;

        friend class Game;

    public:
        Screen();
        ~Screen();

        enum MessageType {
            MESSAGE_EMPTY, MESSAGE_SINGLE, MESSAGE_DOUBLE, 
            MESSAGE_TRIPLE, MESSAGE_TETRIS, MESSAGE_GAME_OVER
        };

        void update_score_window(int) const;
        void update_message_window(MessageType) const;
        void update_main_window(const Board &) const;
        void update_main_window(const Board &, const Block &) const;
};

#endif
