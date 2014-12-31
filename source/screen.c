
#include "system.h"

#define PALETTE_MASK    0x3C6
#define PALETTE_READ    0x3C7
#define PALETTE_WRITE   0x3C8
#define PALETTE_DATA    0x3C9

/*
    Plot a pixel at the specified X and Y coordinate
    
    @param
        x - x coordinate
        y - y coordinate
        color - color of pixel
*/
void putPixel(unsigned short x, unsigned short y, char color) {
    if (x < 320u && y < 200) mempokeb(VIDEO_SEG, y * 320 + x, color);
}

/*
    Set the screen mode
    
    Commonly used modes:
    > 0x03 - 16-color textmode, DOSBox default
    > 0x13 - 256-color VGA graphics, linear memory map
*/
void setScreenMode(char mode) {
    asm("mov ax, [bp + 4]\n"
        "mov ah, 0\n"
        "int 0x10");
}

/*
    Set the color of the specified VGA palette register
    
    @param
        index - palette register index
        red - red intensity
        green - green intensity
        blue - blue intensity
*/
void setPaletteRegister(unsigned char index, unsigned char red, unsigned char green, unsigned char blue) {
    asm("cli");
    outb(PALETTE_MASK, 0xFF);
    outb(PALETTE_WRITE, index);
    outb(PALETTE_DATA, red >> 2);
    outb(PALETTE_DATA, green >> 2);
    outb(PALETTE_DATA, blue >> 2);
    asm("sti");
}
