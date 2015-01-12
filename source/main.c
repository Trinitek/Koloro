
#include "input.h"
#include "screen.h"
#include "file.h"
#include "draw.h"
#include "string.h"

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
    
    // Test string copying
    static char str4[] = "Copy me!";
    static char str5[9];
    
    stringCopy(&str4, &str5);
    print(&str5, 1, 19, 15);
    
    // Test string reversing
    static char str6[] = "Reverse me!";
    static char str7[12];
    print(&str6, 1, 25, 15);
    stringReverse(&str6, &str7);
    print(&str7, 1, 31, 15);
    
    // Test signed integer to string conversion
    static char str8[7];
    intToString(-32767, &str8);
    print(&str8, 1, 37, 15);
    intToString(64, &str8);
    print(&str8, 1, 43, 15);
    intToString(-842, &str8);
    print(&str8, 1, 49, 15);
    intToString(0, &str8);
    print(&str8, 1, 55, 15);
    
    // Test unsigned integer to string conversion
    uintToString(65535u, &str8);
    print(&str8, 1, 61, 15);
    uintToString(0, &str8);
    print(&str8, 1, 67, 15);
    uintToString(542, &str8);
    print(&str8, 1, 73, 15);
    uintToString(32, &str8);
    print(&str8, 1, 79, 15);
    
    uintToString(putChar('.', 50, 50, 14), &str8);
    print(&str8, 50, 56, 14);
    
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
