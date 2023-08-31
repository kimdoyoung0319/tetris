#include "screen.h"

Screen::Screen() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    init_pair(BLACK_AND_WHITE, COLOR_WHITE, COLOR_BLACK);
    main_window = newwin(MAIN_WINDOW_HEIGHT,
                         MAIN_WINDOW_WIDTH,
                         MAIN_WINDOW_POS_Y,
                         MAIN_WINDOW_POS_X);
    wtimeout(main_window, 0);
    box(main_window, 0, 0);
}

Screen::~Screen() {
    delwin(main_window);
    endwin();
}

void Screen::update_main_window(const Board & board) const {
    Coordinate position_board, position_cursor;
    for(int i = 0; i < LENGTH_COL; i++) {
        for(int j = 0; j < LENGTH_ROW; j++) {
            position_board = {j, i};
            if(board.is_filled(position_board))
                draw_square(position_board);
            else
                erase_square(position_board);
        }
    }
    refresh_main_window();

    return;
}

inline void Screen::refresh_main_window() const {
    wrefresh(main_window);
    
    return;
}


void Screen::draw_square(const Coordinate & position_board) const {
    int cursor_position_x = 2 * position_board.x + 1;
    int cursor_position_y = position_board.y + 1;
    mvwaddch(main_window, cursor_position_y, cursor_position_x, ' ' | A_REVERSE | COLOR_PAIR(BLACK_AND_WHITE));
    mvwaddch(main_window, cursor_position_y, cursor_position_x + 1, ' ' | A_REVERSE | COLOR_PAIR(BLACK_AND_WHITE));

    return;
}

void Screen::erase_square(const Coordinate & position_board) const {
    int cursor_position_x = 2 * position_board.x + 1;
    int cursor_position_y = position_board.y + 1;
    mvwaddch(main_window, cursor_position_y, cursor_position_x, ' ' | COLOR_PAIR(BLACK_AND_WHITE));
    mvwaddch(main_window, cursor_position_y, cursor_position_x + 1, ' ' | COLOR_PAIR(BLACK_AND_WHITE));
    
    return;
}
