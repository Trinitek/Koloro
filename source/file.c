
#include "bool.h"

/*
    Write the selected memory block to a file
    
    @param
        *filenameStr - null terminated 8.3 character filename string
        *array - memory block starting address
        arrayLength - size of memory block in bytes
        
    @return
        true if successful
*/
bool os_writeFile(char *filenameStr, char *array, short arrayLength) {
    asm("push es \n"
        "mov si, [bp + 6] \n"   // Copy memory block to buffer
        "mov ax, 0x2000 \n"
        "mov es, ax \n"
        "mov di, [es:32768+2] \n"
        "mov cx, [bp + 8] \n"
        "rep stosb \n"
        "pop es \n");
        
    asm("mov si, [bp + 4] \n"
        "mov cx, [bp + 8] \n"
        "call 0x2000:32768+8 \n"
        "setnc al \n"           // Set AL=1 if carry=0
        "mov ah, 0");           // Sanitize AH
}

/*
    Read the specified file into memory
    
    @param
        *filenameStr - null terminated 8.3 character filename string
        *array - memory block starting address
    
    @return
        size of file in bytes, 0 if not found
*/
short os_readFile(char *filenameStr, char *array) {
    asm("mov ax, [bp + 4]\n"
        "mov cx, [bp + 6]\n"
        "call os_load_file\n"
        
        "jc .error\n"           // If there was no error, copy filesize into AX
        "mov ax, bx\n"
        "jmp .leave\n"
        
        ".error:\n"             // If there was an error, write 0 to AX
        "xor ax, ax\n"
        
        ".leave:\n");
}
