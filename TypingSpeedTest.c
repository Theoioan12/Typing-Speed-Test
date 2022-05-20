#include <stdlib.h>
#include <ncurses.h>

void print(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    mvwprintw(stdscr, yMax / 4, xMax / 2 - 12, ".:|| Website Finder ||:.");
    mvwprintw(stdscr, yMax / 4 + 3, xMax / 2 - 12, ".:|| Website Finder ||:.");
}

int main(){

    initscr();
    curs_set(1);
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    box(stdscr, 0, 0);
    print();
    int x = getch();
    attron(COLOR_PAIR(2));
    for(int i = 0; i < 3; i++){
        box(stdscr, 0, 0);
        int x = getch();
        printw("%d ", x);
        if(x == 127)
            delch();
        attron(COLOR_PAIR(1));
        x = getch();
        if(x == 127)
            delch();
        x = getch();
        if(x == 127)
            delch();
        attron(COLOR_PAIR(2));
        x = getch();
        if(x == 127)
            delch();
        x = getch();
    }
    endwin();
    return 0;
}