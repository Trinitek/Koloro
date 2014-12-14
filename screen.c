
/*
    Use the following commands to compile this file into an executable:
    
    > smlrc -flat16 screen.c screen.asm
    > nasm -o screen.asm screen.com
    
    If you have DOSBox in your PATH variable, you may run the file using the following:
    
    > dosbox screen.com
    
    Happy coding!
*/

// Code starting point -- don't touch this unless you know what you're doing!
// ORG 0x100 means this file will compile to a valid MS-DOS *.COM binary.
    asm("org 0x100");

/*
    Use this function for testing functions. This will not be here in the final version.
*/
void main(void) {
    setMode(0x13);
    
    putPixel(0,0,8);
    
    waitForKey();
    
    return;
}

/*
    Plot a pixel at the specified X and Y coordinate
*/
void putPixel(unsigned short x, unsigned short y, char color) {
    putPixelOfs(y * 200 + x, color);
}

/*
    Plot a pixel at the specified offset in video memory
*/
void putPixelOfs(short offset, char color) {
    asm("mov bx, [bp + 4]\n"
        "mov ax, [bp + 6]\n"
        "mov cx, 0xA000\n"
        "mov ds, cx\n"
        "mov [ds:bx], al\n");
}

/*
    Set the screen mode
    
    Commonly used modes:
    > 0x03 - 16-color textmode, DOSBox default
    > 0x13 - 256-color VGA graphics, linear memory map
*/
void setMode(char mode) {
    asm("mov ax, [bp + 4]\n"
        "mov ah, 0\n"
        "int 0x10");
}