
asm("org 32768");

#include "input.h"
#include "screen.h"
#include "file.h"
#include "draw.h"

void main(void) {
    // Set the video mode to VGA 256-color graphics
    setScreenMode(0x13);
    
    // Put pixels at all four corners of the screen
    putPixel(0, 0, 15);         // top left
    putPixel(320-1, 0, 15);     // top right
    putPixel(320-1, 200-1, 15); // bottom right
    putPixel(0, 200-1, 15);     // bottom left
    waitForKey();
    
    // Fill the screen with boxes
    #define BOXW 80
    #define BOXH 50
    
    char c = 16;
    short x;
    short y;
    for (x = 0; x <= 240; x += 80) {
        for (y = 0; y <= 150; y += 50) {
            fillRectangle(x, y, BOXW, BOXH, c);
            c++;
        }
    }
    
    waitForKey();
    
    // Cycle through some different colors
    setPaletteRegister(16, 255, 255, 0);
    setPaletteRegister(17, 0, 255, 255);
    setPaletteRegister(18, 128, 128, 255);
    setPaletteRegister(19, 0, 127, 255);    // Pakaku's favorite color
    setPaletteRegister(20, 255, 0, 0);
    setPaletteRegister(21, 0, 255, 0);
    setPaletteRegister(22, 0, 0, 255);
    setPaletteRegister(23, 64, 64, 128);
    setPaletteRegister(24, 64, 128, 64);
    
    // Write an array to a file
    char helloFilename[] = "hello.txt\0";
    char hello[] = "Hello world!\0";
    os_writeFile(&helloFilename, &hello, 13);
    
    // Read a file to an array
    /*char hello2[14];
    short helloSize = os_readFile(&helloFilename, &hello2);
    
    for (x = 0; x < helloSize; x++) {
        putPixel(x, 100, 14);
    }
    
    */
    
    waitForKey();
    
    //tScreenMode(0x13);
    //tPaletteRegister(0, 255, 255, 255);
    setPaletteRegister(40, 0, 0, 0);
    
    putPixel(1, 1, 40);
    putPixel(1, 2, 40);
    putPixel(1, 3, 40);
    putPixel(1, 4, 40);
    putPixel(1, 5, 40);
    putPixel(2, 3, 40);
    putPixel(3, 2, 40);
    putPixel(3, 4, 40);
    putPixel(4, 4, 40);
    putPixel(4, 1, 40);
    putPixel(5, 1, 40);
    putPixel(5, 5, 40);
    
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
asm("%include 'draw.asm'");
asm("%include 'file.asm'");
asm("%include 'math.asm'");
asm("%include 'fixed.asm'");
//asm("%include 'state.asm'");

asm("%include '../source/mikedev.inc'");
