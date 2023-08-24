#include <ncursesw/ncurses.h>
#include <unistd.h>

int main(void) {
    initscr();
    //must be used after initscr
    WINDOW * window = newwin(5, 15, 2, 2);
    box(window, 0, 0);
    wrefresh(window);
    wgetch();
    endwin();
    
    return 0;
}