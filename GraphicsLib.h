#ifndef GRAPHICSLIB
#define GRAPHICSLIB

    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <ncurses.h>

    #define DATABASE_NAME "database.txt"
    #define ENTER 10
    #define ESC 27
    #define WHITESPACE 32
    #define BACKSPACE 127

    typedef struct typeText{
        char ch; // current letter
        char status; // letter status
    }typeText;
    
    typedef struct GameData{
        typeText *text; // text
        unsigned int len; // text lenght
        unsigned int nr_tries; // number of key presses
        unsigned int right; // number of correct key presses
        time_t start_t; // start timestamp
        time_t stop_t;  // stop timestamp
        float accuracy; // player accuracy
        float WPM; // words per minute
    }GameData;

    typedef struct Database{
        GameData *arr;
        int nr_items;
    }Database;

    void GL_Menu();
    void GL_Play(GameData *paragraph);
    void GL_Results(GameData *paragraph);

#endif