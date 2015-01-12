
#include "screen.h"
#include "math.h"
#include "bool.h"

/**
    Draws the outline of a rectangle to the screen.
    
    @param
        x - x coordinate
        y - y coordinate
        width - width of the rectangle
        height - height of the rectangle
        c - color of the rectangle
*/
void drawRectangle(short x, short y, short width, short height, char c) {
    int i;
    int newX;
    int newY;
    
    // Draw horizontal lines
    newY = y;
    for (i = 0; i < 2; i++) {
        for (newX = 0; newX < width; newX++) {
            setPixel(newX + x, newY, c);
        }
        newY += height - 1;
    }
    
    // Draw vertical lines
    newX = x;
    for (i = 0; i < 2; i++) {
        for (newY = 0; newY < height; newY++) {
            setPixel(newX, newY + y, c);
        }
        newX += width - 1;
    }
}

/**
    Draws a rectangle with a filled center.
    
    @param
        x - x coordinate
        y - y coordinate
        width - width of the rectangle
        height - height of the rectangle
        c - color of the rectangle
 */
void fillRectangle(short x, short y, short width, short height, char c) {
    int newX;
    int newY;
    for (newX = x; newX < width + x; newX++) {
        for (newY = y; newY < height + y; newY++) {
            setPixel(newX, newY, c);
        }
    }
}

/**
    Draw a line from point (x1, y1) to point (x2, y2)
    
    @param
        x1 - starting x coordinate
        y1 - starting y coordinate
        x2 - ending x coordinate
        y2 - ending x coordinate
        color - color of the line
*/
void drawLine(short x1, short y1, short x2, short y2, char color) {
    short dx = x2 - x1;
    short dy = y2 - y1;
    short newX;
    short newY;
    short absdy = abs(dy);
    
    // Iterate along the X axis if the slope is not steep (m <= 1)
    if (dx >= abs(dy)) {
        for (newX = 0; newX <= dx; newX++) {
            // newY = (dy * newX) / dx
            
            asm("finit \n");                // initialize FPU
            
            asm("fild word [bp - 4] \n"     // push (dy) -> ST1
                "fild word [bp - 6] \n"     // push (newX) -> ST0
                "fmulp \n");                // (dy * newX) -> ST1, release ST0
            
            asm("fild word [bp - 2] \n"     // push (dx) -> ST0
                "fdivp \n");                // ((dy * newX) / dx) -> ST1, release ST0
            
            asm("fist word [bp - 8] \n");   // (newY) = ST0
                
            
            putPixel(newX + x1, newY + y1, color);
        }
    }
    
    // Iterate along the Y axis if the slope is steep (m > 1), including vertical slopes
    else {
        for (newY = 0; newY <= absdy; newY++) {
            // newX = ((dx * newY) / abs(dy));
            
            asm("finit \n");                // initialize FPU
            
            asm("fild word [bp - 2] \n"     // push (dx) -> ST1
                "fild word [bp - 8] \n"     // push (newY) -> ST0
                "fmulp \n");                // (dx * newY) -> ST1, release ST0
            
            asm("fild word [bp - 10] \n"    // push (dy) -> ST0
                "fdivp \n");                // ((dx * newY) / absdy) -> ST1, release ST0
            
            asm("fist word [bp - 6] \n");   // (newX) = ST0
            
            if (dy >= 0) putPixel(newX + x1, newY + y1, color);
            else putPixel(newX + x1, y1 - newY, color);
        }
    }
}

/**
    Draws a circle with a center at (centerX, centerY) and a radius of radius.
    
    @param
        centerX - x coordinate of center
        centerY - y coordinate of center
        radius - radius of the circle
        color - color of the circle
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

/**
    Draws a single dot at this point.
    Is a seperate function from setPixel() because this action will need to be
    recorded for the undo function.
    
    @param
        x - x coordinate
        y - y coordinate
        color - color of pixel
*/
void pencil(short x, short y, char color) {
    setPixel(x, y, color);
}

/**
    Function that draws a pixel to the image being worked on.
    Will mutate a value within the current layer.
    
    @param
        x - x coordinate
        y - y coordinate
        color - color of pixel
*/
void setPixel(short x, short y, char color) {
    putPixel(x, y, color);
}

/**
    Sets the current value in the current layer as translucent
    
    @param
        x - x coordinate
        y - y coordinate
*/
void erasePixel(short x, short y) {
    // TODO: this
}

/**
    Put a 5x5 font character on the current layer
    
    @param
        c - character to write
        x - x coordinate, top left origin
        y - y coordinate, top left origin
        color - color of character
    @return
        width of the character
*/
char putChar(char c, short x, short y, char color) {
    char* glyphOfs = getGlyph(c);
    char byte = 0;
    char i;
    unsigned char pattern = 128u; // 0b10000000
    short xOfs = 0;
    short yOfs = 0;
    char charWidth = 0;
    char lineWidth = 0;
    
    for (i = 0; i < 5*5; i++) {
        // Plot pixel only if bit is set
        if (*(glyphOfs + byte) & pattern) {
            setPixel(x+xOfs, y+yOfs, color);
            lineWidth = xOfs + 1;
        }
        
        // Maximum of 5 pixels per row
        if (!((i + 1) % 5) && i){
            xOfs = 0;
            yOfs++;
            
            if (lineWidth > charWidth) charWidth = lineWidth;
            lineWidth = 0;
        }
        else xOfs++;
        
        // Next string of bits if the pattern is used up
        pattern = pattern >> 1;
        if (!pattern) {
            byte++;
            pattern = 128u;
        }
    }
    
    return charWidth;
}

/**
    Put a string of characters on the current layer
    
    @param
        stringPtr - pointer to null terminated string
        x - x coordinate
        y - y coordinate
        color - color of the characters
*/
void print(char* stringPtr, short x, short y, char color) {
    char c;
    while (true) {
        c = *stringPtr;
        if (!c) break;
        else if (c != ' ') x += putChar(c, x, y, color) + 1;
        else  x += 6;
        
        stringPtr++;
    }
}
