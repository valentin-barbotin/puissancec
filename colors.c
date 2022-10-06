#include <string.h>
#include <stdio.h>

#include "colors.h"

/**
 * print a colored char
 * @param {char*} color
 * @param {const char*} character
 * @return void
 */
void printColoredChar(Color color, char character) {
    int colorCode;

    switch (color)
    {
        case BLACK:
            colorCode = 30;
            break;
        case RED:
            colorCode = 31;
            break;
        case GREEN:
            colorCode = 32;
            break;
        case YELLOW:
            colorCode = 33;
            break;
        case BLUE:
            colorCode = 34;
            break;
        case MAGENTA:
            colorCode = 35;
            break;
        case CYAN:
            colorCode = 36;
            break;
        case WHITE:
            colorCode = 37;
            break;
        
        default:
            break;
    }
    printf("\033[1;%dm%c\033[0m", colorCode, character);
}