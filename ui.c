#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "terminal.h"
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#define FRAME_COUNT 6
#define HORSE_HEIGHT 13
#define HORSE_WIDTH 45

static volatile sig_atomic_t timer_flag = 0;

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

const char horse_frames[FRAME_COUNT][HORSE_HEIGHT][HORSE_WIDTH] = {

    // FRAME 0 : 도약
    {
        "                              /\\  /\\",
        "                             /  \\/  \\",
        "                        ____/        \\",
        "                       /        O     |",
        "     ~~~~~~~          /    /|      ___/",
        "   ~~       \\________/    /  \\____/",
        "             /            |",
        "            /              \\",
        "           |                |",
        "            \\____      ____/",
        "        ____/    \\____/    \\____",
        "   ____/                        \\____",
        "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    },

    // FRAME 1 : 착지 준비
    {
        "                              /\\  /\\",
        "                             /  \\/  \\",
        "                        ____/        \\",
        "                       /        O     |",
        "   ~~~~~~~            /    /|      ___/",
        "          ~~\\________/    /  \\____/",
        "             /            |",
        "            /              \\",
        "           |                |",
        "            \\____      ____/",
        "                 \\    /   |",
        "              ___/   /    \\___",
        "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    },

    // FRAME 2 : 다리를 모으는 자세
    {
        "                              /\\  /\\",
        "                             /  \\/  \\",
        "                        ____/        \\",
        "                       /        O     |",
        "       ~~~~~          /    /|      ___/",
        "   ~~~~     \\________/    /  \\____/",
        "             /            |",
        "            /              \\",
        "           |                |",
        "            \\____      ____/",
        "                 \\    /",
        "                  \\__/",
        "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    },

    // FRAME 3 : 지면을 박차는 자세
    {
        "                              /\\  /\\",
        "                             /  \\/  \\",
        "                        ____/        \\",
        "                       /        O     |",
        "  ~~~~~~~~~           /    /|      ___/",
        "           ~\\________/    /  \\____/",
        "             /            |",
        "            /              \\",
        "           |                |",
        "            \\____      ____/",
        "           /     \\____/    \\",
        "      ____/                 \\____",
        "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    },

    // FRAME 4 : 행복한 말
    {
        "             /\\          /\\",
        "            /  \\________/  \\",
        "           /                \\",
        "          /                  \\",
        "         |    ^        ^      |",
        "         |                    |",
        "         |                    |",
        "         |      .------.      |",
        "         |     (  o  o  )     |",
        "          \\     '------'     /",
        "           \\                /",
        "            \\______________/",
        "              ENJOY THE RIDE!"
    },

    // FRAME 5 : 화난 말
    {
        "       ( (                       ) )",
        "        ) )                     ( (",
        "             /\\          /\\",
        "            /  \\________/  \\",
        "           /    #  #        \\",
        "          /      ##          \\",
        "         |    \\        /      |",
        "         |     >      <       |",
        "         |                    |",
        "         |     .--------.     |",
        "          \\   (  OO  OO  )   /",
        "           \\___'~~~~~~~~'___/",
        "             LET'S GO FASTER!!"
    }
};

// START PAGE 구현
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


// RUNNING PAGE 구현
void draw_horse(WINDOW *win, int frame){
    int height, width;
    getmaxyx(win, height, width);

    int start_y = (height - HORSE_HEIGHT) / 2;
    int start_x = (width - HORSE_WIDTH) / 2;

    werase(win);
    box(win, 0, 0);

    for (int i = 0; i < HORSE_HEIGHT; i++)
    {
        mvwaddstr(win,
                  start_y + i,
                  start_x,
                  horse_frames[frame][i]);
    }

    wrefresh(win);
}

void draw_meter(WINDOW *win, int elapsed, int fare){
    int height, width;
    getmaxyx(win, height, width);
    int minutes = elapsed / 60, seconds = elapsed % 60;

    werase(win);
    box(win, '|' , '-');
    
    wstandout(win);
    mvwprintw(win, (height / 2) , width / 1.2, "TIME : %02d:%02d", minutes, seconds);
    mvwprintw(win, (height / 2) + 1, width / 1.2, "FARE : %d KRW", fare);
    wstandend(win);
    wrefresh(win);
}

void draw_control(WINDOW *win){
    int height, width;
    getmaxyx(win, height, width);
    char outbutton[] = "0: STOP & Pay";

    wstandout(win);
    mvwprintw(win, 0, width - strlen(outbutton), "%s", outbutton);
    wstandend(win);

    wmove(win, height-1, width -1);
    wrefresh(win);
}

int set_timer(int n_msecs){
    struct itimerval new_timeset;
    long n_secs, n_usecs;

    n_secs = (long)(n_msecs / 1000);
    n_usecs = (long)(n_msecs % 1000) * 1000L;

    new_timeset.it_value.tv_sec = n_secs;
    new_timeset.it_value.tv_usec = n_usecs;
    
    new_timeset.it_interval.tv_sec = n_secs;
    new_timeset.it_interval.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void timer_handler(int signo){
    timer_flag = 1;
}

int setup_signal(void)
{
    struct sigaction sa = {0};

    sa.sa_handler = timer_handler;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    return sigaction(SIGALRM, &sa, NULL);
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
    int frame = 0, count = 0;

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

    // 첫 화면 출력
    draw_horse(horse_win, frame);
    draw_meter(meter_win, 120, fare);
    draw_control(control_win);

    if(setup_signal() == -1){
        perror("setup_signal");
    }
    
    if(set_timer(1000) == -1){
        perror(NULL);
    }

    wtimeout(control_win, 50);

    while(1){
         if (timer_flag == 1){
            timer_flag = 0;
            count++;
            frame++;

            if(count < 10){
                frame %= 4;
            }else{
                frame %= FRAME_COUNT;
                fare += 100;
            }

            draw_horse(horse_win, frame);
            draw_meter(meter_win, count, fare);
        }

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
