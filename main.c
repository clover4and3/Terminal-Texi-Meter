#include <stdio.h>
#include <ncurses.h>
#include "terminal.h"
#include "ui.h"

int main(){
    int program_stat;
    int total_fare;
    save_terminal();

    program_stat = draw_start_screen();
    
    if(program_stat == 1){
        // RUNNING PAGE 전환
        total_fare = draw_running_screen();
        draw_payment_screen(total_fare);
    }else if(program_stat == 2){
        // 터미널 되돌리기 & 프로그램 종료 
        set_terminal(1);
        endwin();
    }

    return 0;
}