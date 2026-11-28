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



void draw_horse(WINDOW *win, int frame){
    box(win, 0 , 0);
    wrefresh(win);
}

void draw_meter(WINDOW *win, int elapsed, int fare){
    box(win, '|' , '-');
    
    mvwprintw(win, 2, 2, "FARE : %d KRW", fare);
    wrefresh(win);
}

void draw_control(WINDOW *win){
    mvwprintw(win, 2, 2, "0.STOP and Pay");

    wmove(win, 3,3);
    wrefresh(win);
}

int draw_running_screen(){
    clear();
    refresh();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    
    int horse_height = rows * 0.6;
    int meter_height = rows * 0.2;
    int control_height = rows - horse_height - meter_height;
    int fare = 4000;
    int stop = -1;
    char runningMassage[] = "RUNNING PAGE: ENJOY YOUR DRIVING!";
    
    standout();
    mvprintw(0, (COLS / 2) - (strlen(runningMassage) / 2), "%s" ,runningMassage);
    refresh();
    standend();

    WINDOW *horse_win = newwin(
        horse_height, cols,
        1, 0
    );

    WINDOW *meter_win = newwin(
        meter_height, cols,
        horse_height + 1, 0
    );

    WINDOW *control_win = newwin(
        control_height, cols,
        horse_height + meter_height + 1, 0
    );

    draw_horse(horse_win, 0);
    draw_meter(meter_win, 120, fare);
    draw_control(control_win);

    
    while(1){
        stop = wgetch(control_win);
        
        if(stop == '0'){
            delwin(horse_win);
            delwin(meter_win);
            delwin(control_win);
            
            return fare;
        }
    }
}


int draw_payment_screen(int fare){
    clear();
    refresh();

    getch();

    set_terminal(1);
    endwin();
}
