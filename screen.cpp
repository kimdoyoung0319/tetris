#include "screen.h"

Screen::Screen() {
    initscr();

    noecho();
    curs_set(0);

    cbreak();

    start_color();
    init_pair(WHITE_BLACK_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW_BLACK_PAIR, COLOR_YELLOW, COLOR_BLACK);

    main_window = newwin(main_window_height,
                         main_window_width,
                         main_window_position.y,
                         main_window_position.x);

    score_window = newwin(score_window_height,
                          score_window_width,
                          score_window_position.y,
                          score_window_position.x);
    
    message_window = newwin(message_window_height,
                            message_window_width,
                            message_window_position.y,
                            message_window_position.x);

    wtimeout(main_window, 0);

    box(main_window, 0, 0);
    box(score_window, 0, 0);
    box(message_window, 0, 0);

    mvwprintw(main_window, 0, 1, "Game");
    mvwprintw(score_window, 0, 1, "Score");
    mvwprintw(message_window, 0, 1, "Message");
}

Screen::~Screen() {
    delwin(main_window);
    endwin();
}

void Screen::update_main_window(const Board & board, const Block & block) const {
    for(int i = 0; i < board.col_size; i++) {
        for(int j = 0; j < board.row_size; j++) {
            if(board.is_filled({j, i}))
                draw_square_normal({j, i});
            else
                erase_square({j, i});
        }
    }

    Coordinate position = block.get_position();

    //Because previously drawn squares of board are already existing,
    //you must not erase any empty squares when drawing block.
    for(int i = 0; i < block.col_size; i++) {
        for(int j = 0; j < block.row_size; j++) {
            if(block.is_filled({j, i}))
                draw_square_highlighted({position.x + j, position.y + i});
        }
    }

    refresh_window(main_window);

    return;
}

void Screen::update_main_window(const Board & board) const {
    for(int i = 0; i < board.col_size; i++) {
        for(int j = 0; j < board.row_size; j++) {
            if(board.is_filled({j, i}))
                draw_square_normal({j, i});
            else
                erase_square({j, i});
        }
    }

    refresh_window(main_window);
}

void Screen::draw_square_normal(const Coordinate & coordinate) const {
    Coordinate cursor_coordinate{2 * coordinate.x + 1, coordinate.y + 1};

    //The space character is half-sized,
    //so the game would be looking so weird if you draw a square with just a single mvwaddch() call.
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x, 
            ' ' | A_REVERSE | COLOR_PAIR(WHITE_BLACK_PAIR));
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x + 1, 
            ' ' | A_REVERSE | COLOR_PAIR(WHITE_BLACK_PAIR));

    return;
}

void Screen::draw_square_highlighted(const Coordinate & coordinate) const {
    Coordinate cursor_coordinate{2 * coordinate.x + 1, coordinate.y + 1};

    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x, 
            ' ' | A_REVERSE | COLOR_PAIR(YELLOW_BLACK_PAIR));
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x + 1, 
            ' ' | A_REVERSE | COLOR_PAIR(YELLOW_BLACK_PAIR));

    return;
}

void Screen::erase_square(const Coordinate & coordinate) const {
    Coordinate cursor_coordinate{2 * coordinate.x + 1, coordinate.y + 1};

    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x, 
            ' ' | COLOR_PAIR(WHITE_BLACK_PAIR));
    mvwaddch(main_window, cursor_coordinate.y, cursor_coordinate.x + 1, 
            ' ' | COLOR_PAIR(WHITE_BLACK_PAIR));

    return;
}

void Screen::update_score_window(int score) const {
    Coordinate cursor_coordinate{1, 1};

    mvwprintw(score_window, cursor_coordinate.y, cursor_coordinate.x, "%d", score);
    refresh_window(score_window);

    return;
}

void Screen::update_message_window(MessageType message) const {
    using std::string;

    Coordinate cursor_coordinate{1, 1};
    string message_str;

    switch(message) {
        case MESSAGE_EMPTY:
            message_str = "";
            break;
        case MESSAGE_SINGLE:
            message_str = "Single!";
            break;
        case MESSAGE_DOUBLE:
            message_str = "Double!";
            break;
        case MESSAGE_TRIPLE:
            message_str = "Triple!";
            break;
        case MESSAGE_TETRIS:
            message_str = "Tetris!";
            break;
        case MESSAGE_GAME_OVER:
            message_str = "Game Over!";
            break;
    }

    mvwprintw(message_window,
              cursor_coordinate.y,
              cursor_coordinate.x,
              "%s",
              message_str.c_str());

    refresh_window(message_window);

    return;
}

void Screen::refresh_window(WINDOW * window) const {
    wrefresh(window);
    
    return;
}
