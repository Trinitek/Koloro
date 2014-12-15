
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

/*
    Write a byte to the specified memory location
    
    @param
        segment - destination memory segment
        offset - destination memory offset
        data - byte to write
*/
void mempokeb(short segment, short offset, char data) {
    asm("push es\n"
        "mov ax, [bp + 4]\n"
        "mov es, ax\n"
        "mov di, [bp + 6]\n"
        "mov ax, [bp + 8]\n"
        "stosb\n"
        "pop es");
}

/*
    Write a word to the specified memory location
    
    @param
        segment - destination memory segment
        offset - destination memory offset
        data - word to write
*/
void mempokew(short segment, short offset, short data) {
    asm("push es\n"
        "mov ax, [bp + 4]\n"
        "mov es, ax\n"
        "mov di, [bp + 6]\n"
        "mov ax, [bp + 8]\n"
        "stosw\n"
        "pop es");
}