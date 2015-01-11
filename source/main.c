
#include "input.h"
#include "screen.h"
#include "file.h"
#include "draw.h"

void main(void) {
    // Set the video mode to VGA 256-color graphics
    setScreenMode(0x13);
    
    // Fill the screen with boxes
    #define BOXW 80
    #define BOXH 50
    
    /* char c = 16;
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
    } */
    
    // Cycle through some different colors
    //setPaletteRegister(16, 255, 255, 0);
    //setPaletteRegister(17, 0, 255, 255);
    /*setPaletteRegister(18, 128, 128, 255);
    setPaletteRegister(19, 0, 127, 255);    // Pakaku's favorite color
    setPaletteRegister(20, 255, 0, 0);
    setPaletteRegister(21, 0, 255, 0);
    setPaletteRegister(22, 0, 0, 255);
    setPaletteRegister(23, 64, 64, 128);
    setPaletteRegister(24, 64, 128, 64); */
    
    // Test printing signed and unsigned numbers
    //static char buffer[7];
    
    /* intToString(52, false, &buffer);
    print(&buffer, 1, 1, 15);
    
    intToString(-752, true, &buffer);
    print(&buffer, 1, 6, 15); */
    
    // Test string matching
    static char str1[] = "ABCD";
    static char str2[] = "ABCD";
    static char str3[] = "EFGH";
    static char match[] = "Match!";
    static char nomatch[] = "No match.";
    
    if (stringMatch(&str1, &str2)) print(&match, 1, 1, 15);
    else print(&nomatch, 1, 1, 15);
    
    if (stringMatch(&str1, &str3)) print(&match, 1, 7, 15);
    else print(&nomatch, 1, 7, 15);
    
    if (stringMatch(&str1, &match)) print(&match, 1, 13, 15);
    else print(&nomatch, 1, 13, 15);
    
    waitForKey();
    
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
