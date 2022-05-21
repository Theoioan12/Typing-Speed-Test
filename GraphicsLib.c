#include "GraphicsLib.h"

/* Print menu */
void GL_Menu(){
    int yMax, xMax;
    // Clear stdscr
    clear();
    // Set color to default
    attron(COLOR_PAIR(1));
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
void GL_Play(GameData *paragraph){
    unsigned int len = paragraph->len;
    int yMax, xMax;
    int i;
    int lin, col;
    char color = 1;
    // Clear stdscr
    clear();
    // Set color to default
    attron(COLOR_PAIR(1));
    // Print border
    box(stdscr, 0, 0); // Might remove!
    // Get screen size
    getmaxyx(stdscr, yMax, xMax);
    // Save initial print position
    lin = yMax / 5;
    col = xMax / 7 + 4;
    // Go to the print position
    move(lin, col);
    for(i = 0; i < len; i++){
        if(paragraph->text[i].status != 1 && color == 3){
            // Letter placement
            col++;
            if(paragraph->text[i].ch == ' '){
                if(col > (4 * xMax) / 5){
                    col = xMax / 7;
                    lin++;
                    move(lin, col);
                }
            }
            // Print letter
            printw("%c", paragraph->text[i].ch);
            continue;
        }
        color = paragraph->text[i].status;
        attron(COLOR_PAIR(color));
        // Letter placement
        col++;
        if(paragraph->text[i].ch == ' '){
            if(col > (4 * xMax) / 5){
                col = xMax / 7;
                lin++;
                move(lin, col);
            }
        }
        // Print letter
        printw("%c", paragraph->text[i].ch);
    }
}