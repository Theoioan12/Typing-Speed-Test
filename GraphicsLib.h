#ifndef GRAPHICSLIB
#define GRAPHICSLIB

    #include <stdlib.h>
    #include <string.h>
    #include <inttypes.h>
    #include <time.h>
    #include <ncurses.h>

    typedef struct typeText{
        char ch; // current letter
        int8_t status; // letter status
        time_t timestamp; // timestamp of typing
    }typeText;
    
    typedef struct levelData{
        typeText *text;
        uint32_t len;
        uint32_t nr_tries;
        uint32_t right;
        float accuracy;
        float WPM; 
    }levelData;

#endif