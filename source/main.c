
asm("org 32768");

#include "input.h"
#include "screen.h"

void main(void) {
    // Set the video mode to VGA 256-color graphics
    setScreenMode(0x13);
    
    // Put pixels at all four corners of the screen
    putPixel(0, 0, 15);         // top left
    putPixel(320-1, 0, 15);     // top right
    putPixel(320-1, 200-1, 15); // bottom right
    putPixel(0, 200-1, 15);     // bottom left
    waitForKey();
    
    // Fill a 50x50 box with one color
    short x;
    short y;
    for(x = 0; x < 50; x++) {
        for(y = 0; y < 50; y++) {
            putPixel(x, y, 10);
        }
    }
    waitForKey();
    
    // Cycle through some different colors
    setPaletteRegister(10, 255, 255, 0);
    waitForKey();
    setPaletteRegister(10, 0, 255, 255);
    waitForKey();
    setPaletteRegister(10, 128, 128, 255);
    waitForKey();
    setPaletteRegister(10, 255, 0, 0);
    waitForKey();
    setPaletteRegister(10, 0, 255, 0);
    waitForKey();
    setPaletteRegister(10, 0, 0, 255);
    waitForKey();
    
    // Set the video mode to 16-color 80x25 text
    setScreenMode(0x03);
    
    // MikeOS uses a special attribute setting, where text blinking is disabled
    asm("mov ax, 0x1003\n"
        "mov bx, 0\n"
        "int 0x10");
    
    // Return to the operating system
    return;
}

asm("%include 'input.asm'");
asm("%include 'screen.asm'");
asm("%include 'system.asm'");
asm("%include 'drawutils.asm'");