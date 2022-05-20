#include "search_website.h"
#include "checksum_website.h"
#include <ncurses.h>


void start_page(website *wList, int len);
void search_page(website *wList, int len);
void simple_search(website *wList, int len, char *line);
void complex_search(website *wList, int len, char *line);
void result_screen(website *wList, int len, website *wListSearch, int slen, char *searchLine);
void result_menu(website *wList, int len, website *wListSearch, int slen, char *searchLine, int currentPos);
void website_page(website *wList, int len, website *wListSearch, int slen, char *searchLine, int currentPos);

int main()
{   
    initscr();
    curs_set(0);
    start_color();

    /* Declarare baza de date site-uri */
    website *wList = NULL;
    int len = 0, cap = 3;
    wList = declare_wList(cap);
    /* Citire lista site-uri si memorarea lor */
    read_master(&wList, &cap, &len);
    
    /* Start App */
    start_page(wList, len);

    endwin();
    /* Eliberare memorie wList */
    free_wList(wList, len);
    return 0;
}
/* Afisare pagina de start */
void start_page(website *wList, int len){
    wclear(stdscr);
    noecho();
    /* Obtinere marime fereastra */
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    /* Setare culoare */
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    /* Afiseaza marginile */
    box(stdscr, 0, 0);
    /* Afiseaza textul din pagina de start */
    mvwprintw(stdscr, yMax / 4, xMax / 2 - 12, ".:|| Website Finder ||:.");
    mvwprintw(stdscr, yMax - yMax / 6, xMax / 2 - 12, " C - Search | Q - Close ");
    char input;
    while(1){
        input = getch();
        switch(input)
        {
        case 'q':
            goto endPoint;
            break;
        case 'c':
            search_page(wList, len);
            goto endPoint;
        default:
            break;
        }
    }
    endPoint:;
}
/* Afisare pagina de cautare si citeste query-ul de cautare*/
void search_page(website *wList, int len){
    char input;
    /* Curata fereastra */
    wclear(stdscr);
    /* Setare culoare */
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    /* Obtinere marime fereastra */
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    /* Afiseaza marginile */
    box(stdscr, 0, 0);
    /* Afiseaza textul din pagina de cautare */
    mvwprintw(stdscr, yMax / 4 - 3, xMax / 2 - 12, ".:|| Website Finder ||:.");
    mvwprintw(stdscr, yMax - yMax / 6, xMax / 2 - 40, " Enter - Write / Lock Text | S - Simple search | A - Complex search | Q - Close ");
    /* Creeaza bara de cautare */
    WINDOW *sBox = newwin(3, 103, yMax / 4, xMax / 2 - 51);
    wrefresh(stdscr);
    box(sBox, 0, 0);
    wrefresh(sBox);
    wrefresh(stdscr);
    /* Citeste input */
    input = getch();
    while(input != '\n' && input != 'q')
        input = getch();
    if(input == 'q')
        goto endPoint;
    echo();
    curs_set(1);
    char line[102];
    /* Citeste query-ul de cautare */
    wmove(sBox, 1, 2);
    wgetnstr(sBox, line, 101);
    noecho();
    curs_set(0);
    /* Alege tipul de cautare */
    while(1){
        input = getch();
        switch(input)
        {
        case 'q':
            goto endPoint;
            break;
        case 's':
            delwin(sBox);
            simple_search(wList, len, line);
            goto endPoint;
            break;
        case 'a':
            delwin(sBox);
            complex_search(wList, len, line);
            goto endPoint;
            break;
        default:
            break;
        }
    }

    endPoint:;
}
/* Executa cautarea simpla cu query-ul primit prin variablia line
   si creeaza o lista ordonata de webiste uri pentru rezultat */
void simple_search(website *wList, int len, char *line){
    website *wListSearch = NULL;
    int *wList_ok, slen = 0;
    char lineAux[102];
    strcpy(lineAux, line);
    wList_ok = simple_website_search(wList, len, line);
    show_list_website(simple_cmp, &wListSearch, &slen, wList, wList_ok, len);
    
    /* Curatare fereastra */
    wclear(stdscr);
    wrefresh(stdscr);
    box(stdscr, 0, 0);
    wrefresh(stdscr);
    /* Afisare rezultate cautare simpla */
    result_screen(wList, len, wListSearch, slen, lineAux);
    /* Eliberare memorie */
    free(wListSearch);
    free(wList_ok);
}
/* Executa cautarea complexa cu query-ul primit prin variablia line
   si creeaza o lista ordonata de webiste uri pentru rezultat */
void complex_search(website *wList, int len, char *line){
    website *wListSearch = NULL;
    int *wList_ok, slen = 0;
    char lineAux[102];
    strcpy(lineAux, line);
    wList_ok = complex_website_search(wList, len, line);
    show_list_website(complex_cmp, &wListSearch, &slen, wList, wList_ok, len);
    /* Afisare rezultate cautare complexa */
    result_screen(wList, len, wListSearch, slen, lineAux);   
    /* Eliberare memorie */
    free(wListSearch);
    free(wList_ok);
}
/* Alege si afiseaza ecranul resultatului cautarii in
   functie de site-ul la care se afla cursorul*/
void result_screen(website *wList, int len, website *wListSearch, int slen, char *searchLine){
    int input, currentPos;
    currentPos = 0;
    /* Setare culoare */
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    /* Citire tastatura = true */
    keypad(stdscr, TRUE);
    result_menu(wList, len, wListSearch, slen, searchLine, 0);
    while(1){
        input = getch();
        switch(input)
        {
        case KEY_UP:
            if(currentPos > 0)
                currentPos--;
            result_menu(wList, len, wListSearch, slen, searchLine, currentPos);
            break;
        case KEY_DOWN:
            if(currentPos < slen - 1)
                currentPos++;
            result_menu(wList, len, wListSearch, slen, searchLine, currentPos);
            break;
        case '\n':
            /* Afisare website ales */
            if(slen != 0){
                website_page(wList, len, wListSearch, slen, searchLine, currentPos);
                goto endPoint;
            }
            break;
        case 'b':
            search_page(wList, len);
            goto endPoint;
            break;
        default:
            break;
        }

    }
    endPoint:;
}
/* Afiseaza URL-ul si titlul a 14 site-uri(o pagina) din lista rezultata,
   primita prin wListSearch, in functie de site-ul pe care se afla
   cursorul(currentPos) */
void result_menu(website *wList, int len, website *wListSearch, int slen, char *searchLine, int currentPos){
    /* Curata fereastra */
    wclear(stdscr);
    /* Afiseaza marginile */
    box(stdscr, 0, 0);
    /* Obtinere marime fereastra */
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    /* Afisare logo */
    mvwprintw(stdscr, 5, 2, ".:||WF||:.");
    /* Afisare legenda */
    /* Legenda */
    mvwprintw(stdscr, yMax - yMax / 6, xMax / 2 - 29, " UP/DOWN - Navigation | Enter - Open website | B - Go back ");
    /* Creeaza bara de cautare */
    WINDOW *sBox = newwin(3, 103, 4, 14);
    wrefresh(stdscr);
    box(sBox, 0, 0);
    wrefresh(sBox);
    wrefresh(stdscr);
    mvwprintw(sBox, 1, 1, " %s", searchLine);
    wrefresh(sBox);
    wrefresh(stdscr);
    
    /* Alege pagina */
    int i, maxWebsiteNr = (yMax - 10 - yMax / 6) / 2;
    int first, last;
    first = (currentPos / maxWebsiteNr) * maxWebsiteNr;
    last = first + maxWebsiteNr;
    if(last > slen)
        last = slen;
    /* Afisare pagina resulatae */
    int linePos = 8;
    wmove(stdscr, linePos, 3);
    for(i = first; i < last; i++){
        wmove(stdscr, ++linePos, 14);
        if(i == currentPos){
            /* Setare culoare */
            init_pair(3, COLOR_BLACK, COLOR_WHITE);
            attron(COLOR_PAIR(3));
            wprintw(stdscr, "%s - %s", wListSearch[i].URL, wListSearch[i].title);
            /* Setare culoare */
            init_pair(1, COLOR_WHITE, COLOR_BLACK);
            attron(COLOR_PAIR(1));
        }
        else
            wprintw(stdscr, "%s - %s", wListSearch[i].URL, wListSearch[i].title);
        wmove(stdscr, ++linePos, 14);
    }

    delwin(sBox);
}
/* Afiseaza site-ul de la pozitia selectata(currentPos) */
void website_page(website *wList, int len, website *wListSearch, int slen, char *searchLine, int currentPos){
    /* Curata fereastra */
    wclear(stdscr);
    /* Afiseaza marginile */
    box(stdscr, 0, 0);
    /* Obtinere marime fereastra */
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    wrefresh(stdscr);
    /* Afisare Legenda */
    mvwprintw(stdscr, yMax - yMax / 6, xMax / 2 - 6, " B - Go back ");
    /* Afisare continut website */
    mvwprintw(stdscr, yMax / 8, xMax / 2 - strlen(wListSearch[currentPos].title) / 2, "%s", wListSearch[currentPos].title);
    /* Setare culoare */
    int textColor, backgroundColor;
    //Alegere culoare text
    if(wListSearch[currentPos].textColor == white)
        textColor = COLOR_WHITE;
    if(wListSearch[currentPos].textColor == black)
        textColor = COLOR_BLACK;
    if(wListSearch[currentPos].textColor == red)
        textColor = COLOR_RED;
    if(wListSearch[currentPos].textColor == green)
        textColor = COLOR_GREEN;
    if(wListSearch[currentPos].textColor == blue)
        textColor = COLOR_BLUE;
    if(wListSearch[currentPos].textColor == yellow)
        textColor = COLOR_YELLOW;
    //Alegere culoare fundal
    if(wListSearch[currentPos].backgroundColor == white)
        backgroundColor = COLOR_WHITE;
    if(wListSearch[currentPos].backgroundColor == black)
        backgroundColor = COLOR_BLACK;
    if(wListSearch[currentPos].backgroundColor == red)
        backgroundColor = COLOR_RED;
    if(wListSearch[currentPos].backgroundColor == green)
        backgroundColor = COLOR_GREEN;
    if(wListSearch[currentPos].backgroundColor == blue)
        backgroundColor = COLOR_BLUE;
    if(wListSearch[currentPos].backgroundColor == yellow)
        backgroundColor = COLOR_YELLOW;

    init_pair(2, textColor, backgroundColor);
    attron(COLOR_PAIR(2));
    /* Afisare continut procesat */
    int i, linePos;
    linePos = yMax / 4;
    wmove(stdscr, linePos, 10);
    for(i = 0; i < wListSearch[currentPos].pContent_len; i++){
        if(wListSearch[currentPos].pContent[i] == '\n')
            wmove(stdscr, ++linePos, 10);
        else
            wprintw(stdscr, "%c", wListSearch[currentPos].pContent[i]);
    }
    /* Citire input */
    int input;
    while(1){
        input = getch();
        switch(input)
        {
        case 'b':
            result_screen(wList, len, wListSearch, slen, searchLine);
            /* Setare culoare */
            init_pair(1, COLOR_WHITE, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            wrefresh(stdscr);
            goto endPoint;
            break;
        default:
            break;
        }
    }
    endPoint:;
}