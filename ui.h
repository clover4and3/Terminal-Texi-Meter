#ifndef UI_H
#define UI_H

int draw_start_screen();
int draw_running_screen();
void draw_payment_screen(int fare);
void draw_horse(WINDOW *win, int frame);
void draw_meter(WINDOW *win, int elapsed, int fare);
void draw_control(WINDOW *win);
int set_timer(int n_msecs);
int stop_timer(void);
void timer_handler(int signo);
int setup_signal(void);


#endif