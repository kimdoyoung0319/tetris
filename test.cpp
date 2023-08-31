#include <ncursesw/ncurses.h>
#include <unistd.h>

int main(void) {
    initscr();
    cbreak();
    noecho();
    timeout(0);
    while(true) {
        char user_input = getch();
        if(user_input == ERR)
            printw("ERR\n");
        else
            printw("%c\n", user_input);
        flushinp();
        sleep(1);
    }
    wrefresh(stdscr);
    endwin();
    
    return 0;
}
