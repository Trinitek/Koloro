
char getKey(void) {
    asm("mov ah, 0x10\n"
        "int 0x16\n");
}

void waitForKey(void) {
    while(!getKey());
}