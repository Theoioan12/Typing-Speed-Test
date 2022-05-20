#include "GraphicsLib.h"

/* Print menu */
void GL_Menu(){
    int yMax, xMax;
    // Clear stdscr
    clear();
    // Set color to default
    attron(COLOR_PAIR(0));
    // Print border
    box(stdscr, 0, 0);
    // Get screen size
    getmaxyx(stdscr, yMax, xMax);
    // Print title
    mvprintw(yMax / 3, xMax / 2 - 13, ".:|| Typing Speed Test ||:.");
    // Print commands
    mvprintw(yMax / 2, xMax / 2 - 11, "Enter - Play | Q - Quit");
}
/* Print text at current state */
void GL_Play(GameData *gData){

}