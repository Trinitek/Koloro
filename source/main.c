
#include "input.h"
#include "screen.h"
#include "file.h"
#include "draw.h"

/*asm("jmp asm_start \n"
    "db \"Seg3000!\",0 \n" // 8 chars + null = 9 total
    "asm_start:");*/

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
    
    waitForKey();
    
    putChar('A', 30, 60, 19);
    putChar('B', 36, 60, 20);
    putChar(0, 42, 60, 22);
    
    waitForKey();
    
    /*
    
    // Write an array to a file
    char helloFilename[] = "hello.txt\0";
    char hello[] = "Hello world!\0";
    //setScreenMode(0x03);
    bool status = saveFile(&helloFilename, 0x3000, &hello, 13);
    waitForKey();
    setScreenMode(0x13);
    if (!status) {
        setPaletteRegister(0, 255, 0, 0);
    } else {
        setPaletteRegister(0, 0, 192, 0);
    }
    
    waitForKey();
    
    // Put the letter K onto the screen
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
    
    // Read a file into an array
    short bytesLoaded = loadFile(&helloFilename, 0x2000, 32768u + 256);
    if (bytesLoaded > 0) {
        setPaletteRegister(0, 0, 0, 255);
    } else setPaletteRegister(0, 255, 64, 64);
    
    waitForKey();
    
    */
    
    // Set the video mode to 16-color 80x25 text
    setScreenMode(0x03);
    
    // MikeOS uses a special attribute setting, where text blinking is disabled
    asm("mov ax, 0x1003\n"
        "mov bx, 0\n"
        "int 0x10");
    
    // Return to the operating system
    asm("leave \n"
        "retf");
}
