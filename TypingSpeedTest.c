#include "GraphicsLib.h"

void NCURSES_init();
void NCURSES_free();

void menu();
void run();

int main(){
    // Start app
    run();

    return 0;
}
// Initialize ncurses screen
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
// Free ncruses screen
void NCURSES_free(){
    // Free win
    endwin();
}
// Run app
void run(){
    NCURSES_init();
    menu();
    NCURSES_free();
}
// App's main menu
void menu(){
    // Print menu
    GL_menu();
    // Read input
    int input;
    while(1){
        input = getch();
        if(input == ESC)
            break;
        if(input == ENTER)
            printw("Play\n");
    }
}
