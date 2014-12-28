
#include "bool.h"
#include "system.h"

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
    asm("mov bx, [bp - 2] \n"
        "mov cx, [bp + 10] \n"
        "call 0x2000:32768+6 \n"
        "setnc al \n"
        "mov ah, 0");   // The value in AX will be the return value
}

short loadFile(char *filenameStr_ptr, short destSeg, short destOfs) {
    short bufferOfs = 32768u + 256;
    
    // Copy null-terminated filename to the beginning of the buffer
    char c;
    do {
        c = *filenameStr_ptr;
        mempokeb(0x2000, bufferOfs, c);
        filenameStr_ptr++;
        bufferOfs++;
    } while (c != 0);
    
    // Call operating system API to write data from disk to buffer
    short fileSize;
    
    asm("call 0x2000:32768+2\n"
        "jc .error \n"          // If there was no error, copy filesize into AX
        "mov ax, bx \n"
        "jmp .leave \n"
        ".error: \n"            // If there was an error, write 0 to AX
        "xor ax, ax \n"
        ".leave: \n"
        "mov [bp - 6], ax");    // fileSize = AX
    
    // Copy data from buffer to destination if there was no error
    if (fileSize > 0) {
        memcopy(0x2000, 32768u + 256, destSeg, destOfs, fileSize);
    }
    
    return fileSize;
}
