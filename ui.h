#ifndef UI_H
#define UI_H

int draw_start_screen();
int draw_running_screen();
void draw_horse(WINDOW *win, int frame);
void draw_meter(WINDOW *win, int elapsed, int fare);
void draw_control(WINDOW *win);
int draw_payment_screen(int fare);


#endif