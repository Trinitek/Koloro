
#include "bool.h"
#include "system.h"
#include "input.h"
#include "screen.h"

/*
    Write the selected memory block to a file
    
    @param
        bufferOfs - pointer offset to beginning of data buffer above filename
        size - size of memory block in bytes
        
    @return
        true if successful
*/
bool os_writeFile(short bufferOfs, short size) {
    asm("mov bx, [bp + 4] \n"
        "mov cx, [bp + 6] \n"
        "call 0x2000:32768+6 \n"
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
short os_readFile(char *filenameStr_ptr, char *array) {
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

bool saveFile(char *filenameStr_ptr, short sourceSeg, short sourceOfs, short size) {
    short bufferOfs = 32768u + 256;
    
    // Copy null-terminated filename to the beginning of the buffer
    char c;
    do {
        c = *filenameStr_ptr;
        mempokeb(0x2000, bufferOfs, c);
        filenameStr_ptr++;
        bufferOfs++;
    } while (c != 0);
    
    // Copy data to the buffer, concatenated directly at the end of the filename
    memcopy(sourceSeg, sourceOfs, 0x2000, bufferOfs, size);
    
    // Call operating system API to write the data to disk
    return os_writeFile(bufferOfs, size);
}
