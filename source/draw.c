
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
void drawLine(short x1, short y1, short x2, short y2, char c) {
    // The difference between the two point's y values.
    int y = y2 - y1;

    // The difference between the two point's x values.
    int x = x2 - x1;

    // Iterate through all the x values that the line will be drawn in.
    // Between x1 (start) and x2 (finish).
    int i;
    for (i = x1; i < x2; i++) {
        // For each x that the line is a function of, determine the y at this point.
        // Written in the format y = mx + b.
        //             m|slope * x + b
        int yAtPoint = (y / x) * i + y1;

        // Set the pixel at i (x) and yAtPoint (y) to color c.
        setPixel(i, yAtPoint, c);
    }
}

/*
    Function that draws a pixel to the image being worked on.
    */
void setPixel(short x, short y, char color) {
    putPixel(x, y, color);
}