#include "GraphicsLib.h"

void NCURSES_init();
void NCURSES_free();
Database *Database_setup();
int Database_read(GameData *item, FILE *read);
void *Database_free(Database *database);
void play(GameData *paragraph);
void menu(Database *database);
void run();

int main(){
    // Start app
    run();
    //test
    // Database *d = Database_setup();
    // Database_free(d);
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
Database *Database_setup(){
    // Open file
    FILE *read = fopen(DATABASE_NAME, "rt");
    if(read == NULL)
        return NULL;
    // Initilize database
    Database *database;
    database = (Database*)malloc(sizeof(Database));
    if(database == NULL){
        fclose(read);
        return NULL;
    }
    int nr_items;
    int i;
    // Read number of paragraphs
    fscanf(read, "%d", &nr_items);
    database->nr_items = nr_items;
    // Initialize paragraphs array
    database->arr = (GameData*)malloc(nr_items * sizeof(GameData));
    if(database->arr == NULL){
        free(database);
        fclose(read);
        return NULL;
    }
    // Read every paragraph from database
    for(i = 0; i < nr_items; i++){
        if(Database_read(&(database->arr[i]), read) == -1){
            database->nr_items = i;
            database = Database_free(database);
            break;
        }
    }
    // Close file
    fclose(read);

    return database;
}
/* Read paragraph */
int Database_read(GameData *paragraph, FILE *read){
    char ch;
    int len;
    int i;
    // Read text len
    fscanf(read, "%d", &len);
    paragraph->len = len;
    // Initialize text
    paragraph->text = (typeText*)malloc(len * sizeof(typeText));
    if(paragraph->text == NULL)
        return -1;
    // Read characters
    fgetc(read);
    for(i = 0; i < len; i++){
        fscanf(read, "%c", &ch);
        paragraph->text[i].ch = ch;
        paragraph->text[i].status = 0;
    }
    paragraph->pos = 0;
    paragraph->nr_tries = 0;
    paragraph->right = 0;
    paragraph->accuracy = (float)0;
    paragraph->WPM = (float)0;

    return 0;
}
/* Free database */
void *Database_free(Database *database){
    int i;
    for(i = 0; i < database->nr_items; i++)
        free(database->arr[i].text);
    free(database->arr);
    free(database);
    return NULL;
}



/* Run app */
void run(){
    NCURSES_init();
    srand(time(NULL));
    Database *database = Database_setup();
    if(database == NULL){
        NCURSES_free();
        return;
    }
    menu(database);
    database = Database_free(database);
    NCURSES_free();
}
/* App's main menu */
void menu(Database *database){
    // Print menu
    GL_Menu();
    // Read input
    int input;
    while(1){
        input = getch();
        if(input == 'q' || input == 'Q')
            break;
        if(input == ENTER)
            play(&(database->arr[rand() % (database->nr_items)]));
    }
}

void play(GameData *paragraph){
    printw("Play%d\n", paragraph->len);
}