
asm("org 32768");

#include "input.h"
#include "screen.h"

void main(void) {
    setMode(0x13);
    
    putPixel(0,0,8);
    
    waitForKey();
    
    return;
}

asm("%include 'input.asm'");
asm("%include 'screen.asm'");