#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include "terminal.h"

static struct termios orig_mode;

void save_terminal(){
    tcgetattr(0, &orig_mode);
}

void set_terminal(int mode){
    struct termios ttyinfo;

    if(mode == 1){
        // back to origin tty setting
        tcsetattr(0, TCSANOW, &orig_mode);
        return ;
    }

    if(tcgetattr(0, &ttyinfo) == -1){
        perror("tcgetattr");
    }

    // mode 0 -> 세팅 값 0에 저장
    if(mode == 0){
        ttyinfo.c_lflag &= ~ICANON;
        ttyinfo.c_lflag &= ~ECHO;
        ttyinfo.c_cc[VMIN] = 1;

        if(tcsetattr(0, TCSANOW, &ttyinfo) == -1){
            perror("tcsetattr");
        }
    }

    return;
}

