
/*
    Send a byte to the specified I/O port
*/
void outb(char port, char data) {
    asm("mov dx, [bp + 4]\n"
        "mov ax, [bp + 6]\n"
        "out dx, al");
}

/*
    Send a 16-bit word to the specified I/O port
*/
void outw(char port, short data) {
    asm("mov dx, [bp + 4]\n"
        "mov ax, [bp + 6]\n"
        "out dx, ax");
}