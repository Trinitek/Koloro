
#include "screen.h"

/*
    Draws the outline of a rectangle to the screen.
    */
void drawRectangle(short x, short y, short width, short height, char c) {
        int i;
        int j;
        for (i = x; i < width; i++) {
            for (j = y; j < height; j++) {
                if(i != x && i != x + width) {
                    if(j != y && j != y + height) {
                        setPixel(x, y, c);
                    }
                }
            }
        }
    }

/*
    Draws a rectangle with a filled center.
 */
void fillRectangle(short x, short y, short width, short height, char c) {
    int i;
    int j;
    for (i = x; i < width; i++) {
        for (j = y; j < height; j++) {
            setPixel(i, j, c);
        }
    }
}

/*
    Draw a line from point (x1, y1) to point (x2, y2)
    */
void drawLine(short x1, short y1, short x2, short y2) {
    int y = y2 - y1;
    int x = x2 - x1;

    int i;
    for (i = x1; i < x2; i++) {
        int yAtPoint = i * y / x + y1;
        setPixel(i, yAtPoint);
    }
}

/*
    Function that draws a pixel to the image being worked on.
    */
void setPixel(short x, short y, char color) {
    putPixel(x, y, color);
}