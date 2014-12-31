
#include "screen.h"
#include "math.h"

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
    for (i = x; i < width + x; i++) {
        for (j = y; j < height + y; j++) {
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
    Draws a circle with a center at (centerX, centerY) and a radius of radius.
    */
void drawCircle(short centerX, short centerY, short radius, char color) {
    short angle = 0;

    while(angle < 628) {
        short xVal = centerX + (radius * cos(angle / 100));
        short yVal = centerY + (radius * sin(angle / 100));
        putPixel(xVal, yVal, color);
        angle++;
    }
}

/*
    Draws a single dot at this point.
    Is a seperate function from setPixel() because this action will need to be
    recorded for the undo function.
   */
void pencil(short x, short y, char color) {
    setPixel(x, y, color);
}

/*
    Function that draws a pixel to the image being worked on.
    Will mutate a value within the current layer.
    */
void setPixel(short x, short y, char color) {
    putPixel(x, y, color);
}

/*
    Sets the current value in the current layer as translucent.
    */
void erasePixel(short x, short y) {
    // TODO: this
}

void putChar(char c, short x, short y, char color) {
    char* glyphOfs = getGlyph(c);
    char byte = 0;
    char i;
    unsigned char pattern = 128u; // 0b10000000
    short xOfs = 0;
    short yOfs = 0;
    
    for (i = 0; i < 5*5; i++) {
        // Plot pixel only if bit is set
        if (*(glyphOfs + byte) & pattern) setPixel(x+xOfs, y+yOfs, color);
        
        // Maximum of 5 pixels per row
        if (!((i + 1) % 5) && i){
            xOfs = 0;
            yOfs++;
        }
        else xOfs++;
        
        // Next string of bytes if the pattern is used up
        pattern = pattern >> 1;
        if (!pattern) {
            byte++;
            pattern = 128u;
        }
    }
}
