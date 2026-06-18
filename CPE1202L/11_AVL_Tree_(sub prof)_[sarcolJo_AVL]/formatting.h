/*
======================================================
FILE        : formatting.h
AUTHORS     : Sarcol, Joshua
DESCRIPTION : text formatting definitions
                  changes made here will change how certain words will look in the program globally
              uses ANSI escape sequences
COPYRIGHT   : 2024-03-31

REVISION HISTORY
Date                By              Description
2024-03-26          

======================================================
*/

#ifndef FORMATTING_H
    #define FORMATTING_H

    // reset text alterations
    #define TEXT_RESET printf("\e[m")

    // only one of the following text alterations can be applied at a time
        // applies bold to text
        #define BOLD_TEXT printf("\e[1m")
        
        // applies color to text
        #define COLOR_RED printf("\e[91m")
        #define COLOR_GREEN printf("\e[92m")
        #define COLOR_BLUE printf("\e[94m")
        #define COLOR_PINK printf("\e[95m") 

    // moves cursor by 'x' spaces
    #define MOVE_UP(x) printf("\e[%dA", x)
    #define MOVE_DOWN(x) printf("\e[%dB", x)
    #define MOVE_LEFT(x) printf("\e[%dD", x)

#endif