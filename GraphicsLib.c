#include "GraphicsLib.h"

// Print menu
void GL_menu(){
    int yMax, xMax;
    // Set color to default
    attron(COLOR_PAIR(0));
    // Clear stdscr
    clear();
    // Get screen size
    getmaxyx(stdscr, yMax, xMax);
    // Print title
    mvprintw(yMax / 4, xMax / 2 - 12, ".:|| Typing Speed Test ||:.");
    //move(yMax / 4 + 1, 0);



}