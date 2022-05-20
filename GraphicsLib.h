#ifndef GRAPHICSLIB
#define GRAPHICSLIB

    #include <stdlib.h>
    #include <string.h>
    #include <inttypes.h>
    #include <time.h>
    #include <ncurses.h>

    #define DATABASE "database.txt"
    #define ENTER 10
    #define ESC 27
    #define WHITESPACE 32
    #define BACKSPACE 127

    typedef struct typeText{
        char ch; // current letter
        int8_t status; // letter status
        time_t timestamp; // timestamp of typing
    }typeText;
    
    typedef struct levelData{
        typeText *text; // text
        uint32_t len; // text lenght
        uint32_t pos; // current position
        uint32_t nr_tries; // number of key presses
        uint32_t right; // number of correct key presses
        float accuracy; // player accuracy
        float WPM; // words per minute
    }levelData;

    void GL_menu();

#endif