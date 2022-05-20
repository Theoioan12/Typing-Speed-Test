#ifndef GRAPHICSLIB
#define GRAPHICSLIB

    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <ncurses.h>

    #define DATABASE_NAME "database.txt"
    #define ENTER 10
    #define WHITESPACE 32
    #define BACKSPACE 127

    // Debug
    #define printnl printf("\n")
    #define sprint(x) printf("%d ", (x))
    #define nprint(x) printf("%d\n", (x))

    typedef struct typeText{
        char ch; // current letter
        char status; // letter status
        time_t timestamp; // timestamp of typing
    }typeText;
    
    typedef struct GameData{
        typeText *text; // text
        unsigned int len; // text lenght
        unsigned int nr_tries; // number of key presses
        unsigned int right; // number of correct key presses
        float accuracy; // player accuracy
        float WPM; // words per minute
    }GameData;

    typedef struct Database{
        GameData *arr;
        int nr_items;
    }Database;

    void GL_Menu();
    void GL_Play(GameData *paragraph);

#endif