
// Code starting point; 0x100 means this binary will be a valid MS-DOS *.COM executable
asm("org 0x100");

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