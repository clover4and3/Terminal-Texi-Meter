#include <stdio.h>
#include <ncurses.h>

int draw_start_screen(){
    initscr();
    printw("Hello!");
    refresh();
    getch();
    endwin();

    return 0;
}