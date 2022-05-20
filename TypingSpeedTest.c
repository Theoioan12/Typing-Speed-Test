#include "GraphicsLib.h"

void NCURSES_init();
void NCURSES_free();



void run();

int main(){

    run();

    return 0;
}

void NCURSES_init(){
    // Initialize screen
    initscr();
    // Don't show cursor
    curs_set(0);
    // Don't disply input characters
    noecho();
    // Initialize color
    start_color();
    // Right color pair
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    // Wrong color pair
    init_pair(2, COLOR_WHITE, COLOR_RED);
}
void NCURSES_free(){
    // Free win
    endwin();
}



void run(){
    NCURSES_init();
    attron(COLOR_PAIR(2));
    char x = getch();
    printw("%c ", x);
    attron(COLOR_PAIR(1));
    x = getch();
    printw("%c ", x);
    x = getch();
    printw("%c ", x);
    x = getch();
    printw("%c ", x);
    NCURSES_free();
}
