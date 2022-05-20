#include "GraphicsLib.h"

void NCURSES_init();
void NCURSES_free();

void menu(GameData **database);
void run();

int main(){
    // Start app
    run();

    return 0;
}
/* Initialize ncurses screen */
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
/* Free ncruses screen */
void NCURSES_free(){
    // Free win
    endwin();
}
/* Initialize game database */
GameData **Database_setup(){
    GameData **database;
    database = (GameData**)malloc(sizeof(GameData*));
    return database;
}
/* Run app */
void run(){
    NCURSES_init();
    srand(time(NULL));
    GameData **database = Database_setup();
    menu(database);
    NCURSES_free();
}
/* App's main menu */
void menu(GameData **database){
    // Print menu
    GL_Menu();
    // Read input
    int input;
    while(1){
        input = getch();
        if(input == 'q' || input == 'Q')
            break;
        if(input == ENTER)
            printw("Play\n");
    }
}
