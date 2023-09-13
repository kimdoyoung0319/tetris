#include <ncursesw/ncurses.h>

int main() {
    initscr();
    curs_set(0);
    
    WINDOW * main_window = newwin(23, 22, 1, 1);
    WINDOW * score_window = newwin(5, 10, 1, 24);
    WINDOW * next_block_window = newwin(10, 10, 6, 24);
    WINDOW * message_window = newwin(5, 10, 16, 24);

    box(main_window, 0, 0);
    box(score_window, 0, 0);
    box(next_block_window, 0, 0);
    box(message_window, 0, 0);

    mvwprintw(main_window, 0, 1, "Game");
    mvwprintw(score_window, 0, 1, "Score");
    mvwprintw(next_block_window, 0, 1, "Next");
    mvwprintw(message_window, 0, 1, "Message");

    wrefresh(main_window);
    wrefresh(score_window);
    wrefresh(next_block_window);
    wrefresh(message_window);

    return 0;
}
