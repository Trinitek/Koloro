
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
    
    for (x = 0; x <= 240; x += 80) {
        for (y = 0; y <= 150; y += 50) {
            drawRectangle(x, y, BOXW, BOXH, c);
            c++;
        }
    }
    
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
    
    // Draw some lines
    
    drawLine(0, 0, 199, 199, 0);
    drawLine(0, 199, 199, 0, 0);
    
    drawLine(319-199, 0, 319, 199, 0);
    drawLine(319-199, 199, 319, 0, 0);

    drawLine(200, 0, 250, 199, 0);
    drawLine(320-200, 0, 200, 199, 0);
    drawLine(320-200, 199, 200, 0, 0);
    
    drawLine(0, 0, 50, 199, 0);
    drawLine(10, 0, 50, 199, 0);
    drawLine(50, 0, 50, 199, 0);
    drawLine(250, 0, 300, 199, 0);
    
    drawLine(0, 125, 100, 125, 0);
    drawLine(55, 50, 55, 150, 0);       // vertical line, top to bottom
    drawLine(60, 150, 60, 50, 0);       // vertical line, bottom to top
    drawLine(0, 0, 320-1, 200-1, 0);
    drawLine(0, 200-1, 320-1, 0, 0);
    
    drawLine(0, 0, 319, 1, 0);
    
    waitForKey();
    
    // Rainbow lines from top left corner
    for (y = 0; y < 200; y++) {
        drawLine(50, 0, 319, y, c);
        c++;
    }
    for (x = 319; x >= 0; x--) {
        drawLine(50, 0, x, 199, c);
        c++;
    }
    
    // Rainbow lines from bottom left corner
    for (y = 199; y >= 0; y--) {
        drawLine(50, 199, 319, y, c);
        c++;
    }
    for (x = 319; x >= 0; x--) {
        drawLine(50, 199, x, 0, c);
        c++;
    }
    
    waitForKey();
    
    /* char printTest[] = "This is a test string!";
    print(&printTest, 20, 20, 0);
    char printTest2[] = "Hello world! ABC XYZ";
    print(&printTest2, 20, 26, 1);
    
    waitForKey(); */
    
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
