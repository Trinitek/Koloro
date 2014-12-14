
/*
    Get keyboard code from keyboard controller via BIOS interrupt
*/
char getKey(void) {
    asm("mov ah, 0x10\n"
        "int 0x16\n");
}

/*
    Wait for a keypress
*/
void waitForKey(void) {
    while(!getKey());
}