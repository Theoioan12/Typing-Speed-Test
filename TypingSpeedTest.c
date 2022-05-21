#include "GraphicsLib.h"

void NCURSES_init();
void NCURSES_free();
int Database_read(GameData *item, FILE *read);
void *Database_free(Database *database);
Database *Database_setup();
void Paragraph_reset(GameData *item);
void results(GameData *paragraph);
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
    // Default color pair
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    // Right color pair
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    // Wrong color pair
    init_pair(3, COLOR_WHITE, COLOR_RED);
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
        paragraph->text[i].status = 1;
    }
    paragraph->nr_tries = 0;
    paragraph->right = 0;
    paragraph->start_t = 0;
    paragraph->stop_t = 0;
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
/* Reset paragraph*/
void Paragraph_reset(GameData *paragraph){
    unsigned int len = paragraph->len;
    int i;
    for(i = 0; i < len; i++){
        paragraph->text[i].status = 1;
    }
    paragraph->nr_tries = 0;
    paragraph->right = 0;
    paragraph->start_t = 0;
    paragraph->stop_t = 0;
    paragraph->accuracy = (float)0;
    paragraph->WPM = (float)0;
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
    int random;
    // Read input
    int input;
    while(1){
        // Print menu
        GL_Menu();
        input = getch();
        if(input == 'q' || input == 'Q')
            break;
        if(input == ENTER){
            random = rand() % (database->nr_items);
            play(&(database->arr[random]));
            Paragraph_reset(&(database->arr[random]));
        }
    }
}
/* Play screen */
void play(GameData *paragraph){
    unsigned int len = paragraph->len;
    unsigned int pos = 0;
    int typo;
    int i;
    char ch;
    // Main loop
    while(pos != len + 1){
        // Print text
        GL_Play(paragraph);
        ch = getch();
        // Get start time
        if(paragraph->start_t == 0)
            paragraph->start_t = time(NULL);
        (paragraph->nr_tries)++;
        // Special case for the last character
        if(pos == len){
            // Delete character
            if(ch == BACKSPACE){
                (paragraph->nr_tries)--;
                pos--;
                paragraph->text[pos].status = 1;
                continue;
            }
            else
                continue; 
        }
        // Delete character
        if(ch == BACKSPACE){
            (paragraph->nr_tries)--;
            if(pos == 0)
                continue;
            pos--;
            paragraph->text[pos].status = 1;
            continue;
        }
        // Check match
        if(ch == paragraph->text[pos].ch){
            paragraph->text[pos].status = 2;
            (paragraph->right)++;
        }
        else
            paragraph->text[pos].status = 3;
        // Test if the text have a typo
        if(pos == len - 1){
            typo = 0;
            for(i = 0; i < len; i++){
                if(paragraph->text[i].status == 3){
                    typo = 1;
                    break;
                }
            }
            if(typo == 0)
                break;
        }
        pos++;
    }
    // Get stop time
    paragraph->stop_t = time(NULL);
    // Process results
    paragraph->WPM = ((float)len * 12) / (paragraph->stop_t - paragraph->start_t);
    paragraph->accuracy = ((float)paragraph->right / paragraph->nr_tries) * 100;
    // Go to restults screen
    results(paragraph);
}
/* Results menu */
void results(GameData *paragraph){
    // Print results
    GL_Results(paragraph);
    // Read input
    int input;
    while(1){
        input = getch();
        if(input == 'q' || input == 'Q'){
            break;
        }
        if(input == ENTER){
            Paragraph_reset(paragraph);
            play(paragraph);
            break;
        }
    }
}