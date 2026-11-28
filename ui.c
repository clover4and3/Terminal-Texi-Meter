#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "terminal.h"

const char *start_screen[] = {
    "+------------------------------------------------+",
    "|                                                |",
    "|              J A E Y E O L'S                   |",
    "|              T E R M I N A L                   |",
    "|             T A X I  M E T E R                 |",
    "|                                                |",
    "|                   /\\    /\\                     |",
    "|                  /  \\__/  \\                    |",
    "|                 /          \\                   |",
    "|                |   o    o   |                  |",
    "|                |            |                  |",
    "|                |   .----.   |                  |",
    "|                 \\  ( oo )  /                   |",
    "|                  \\  '--'  /                    |",
    "|                   '------'                     |",
    "|                                                |",
    "|            Ready for a happy ride?             |",
    "|                                                |",
    "|                   [1] START                    |",
    "|                   [2] EXIT                     |",
    "|                                                |",
    "+------------------------------------------------+"
};


int draw_start_screen(){
    initscr();
    clear();
    int program_start;
    //stty ECHO and ICANON 조작 ON
    set_terminal(0);

    int height = sizeof(start_screen) / sizeof(start_screen[0]);
    int width = strlen(start_screen[0]);
    int i, start_height = (LINES - height) / 2, start_width = (COLS - width) / 2;

    for(i = 0; i < height; i++){
        move(start_height, start_width);
        addstr(start_screen[i]);
        start_height ++;
    }
    refresh();
    
    move(LINES - 1, COLS-1);

    while(1){
        program_start = getch();

        if(program_start == '1')
            return 1;
        if(program_start == '2'){
            return 2;
        }

        // 1,2 아닌 경우 예외처리? 안내문자?
    }
}