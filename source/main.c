
asm("org 32768");

#include "input.h"
#include "screen.h"

void main(void) {
    setMode(0x13);
    
    putPixel(0,0,12);
    
    waitForKey();
    
    setMode(0x03);
    return;
}

asm("%include 'input.asm'");
asm("%include 'screen.asm'");