
asm("org 32768");

#include "input.h"
#include "screen.h"

void main(void) {
    setMode(0x13);
    
    short x = 0;
    short y = 0;
    
    for(x; x < 50; x++) {
        for(y; y < 50; y++) {
            putPixel(x, y, 10);
        }
    }
    
    waitForKey();
    
    setPaletteRegister(10, 255, 255, 0);
    waitForKey();
    
    setMode(0x03);
    return;
}

asm("%include 'input.asm'");
asm("%include 'screen.asm'");
asm("%include 'system.asm'");