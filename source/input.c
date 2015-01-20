
#include "input.h"
#include "system.h"

//enum mouse_timeout { DATA, SIGNAL };

// Old mouse interrupt vectors
static unsigned short old_mouseInt_seg;
static unsigned short old_mouseInt_ofs;

char mouse_data;
char mouse_dx;
char mouse_dy;
short mouse_rawX;
short mouse_rawY;
char mouse_scaleX;
char mouse_scaleY;
short mouse_posX;
short mouse_posY;
short mouse_minX;
short mouse_minY;
short mouse_limX;
short mouse_limY;

bool mouse_changed;

/**
    Get keyboard code from keyboard controller via BIOS interrupt
*/
char getKey(void) {
    asm("mov ah, 0x10\n"
        "int 0x16\n");
}

/**
    Wait for a keypress
*/
void waitForKey(void) {
    while(!getKey());
}

void mouseWait(enum mouse_timeout type) {
    unsigned short timeout = 65535u;
    
    if (type == DATA)
        while (timeout--)
            if (inb(PS2_STATUS_PORT) && 1) return;
    
    else
        while (timeout--)
            if (inb(PS2_STATUS_PORT) && 2) return;
}

char mouseRead(void) {
    mouseWait(DATA);
    return inb(PS2_DATA_PORT);
}

void mouseWrite(char data) {
    mouseWait(SIGNAL);
    outb(PS2_COMMAND_PORT, 0xD4);
    mouseWait(DATA);
    outb(PS2_DATA_PORT, data);
}

/**
    Initialize the mouse
*/
void mouseInit(void) {
    char status;
    
    // Enable auxiliary mouse device
    mouseWait(SIGNAL);
    outb(PS2_COMMAND_PORT, 0xA8);
    
    // Enable interrupts
    mouseWait(SIGNAL);
    outb(PS2_COMMAND_PORT, 0x20);
    
    mouseWait(DATA);
    status = (inb(PS2_DATA_PORT) | 2);
    
    mouseWait(SIGNAL);
    outb(PS2_COMMAND_PORT, 0x60);
    
    mouseWait(SIGNAL);
    outb(PS2_DATA_PORT, status);
    
    // Use default settings
    mouseWrite(0xF6);
    mouseRead(); // Acknowledge
    
    // Enable mouse
    mouseWrite(0xF4);
    mouseRead(); // Acknowledge
    
    // Setup mouse handler
}

/**
    Install the mouse interrupt handler
*/
void mouseInstall(void) {
    // Disable interrupts
    asm("cli");
    
    // Preserve old interrupt vector
    old_mouseInt_ofs = mempeekw(0x0000, 0x01D0);
    old_mouseInt_seg = mempeekw(0x0000, 0x01D2);
    
    // Point interrupt vector to new mouse handler
    mempokew(0x0000, 0x01D0, mouseInterruptHandler);
    mempokew(0x0000, 0x01D2, PROGRAM_SEG);
    
    // Reenable interrupts
    asm("sti");
    
    return;
}

/**
    Uninstall the mouse interrupt handler
*/
void mouseUninstall(void) {
    asm("cli");
    
    mempokew(0x0000, 0x01D0, old_mouseInt_ofs);
    mempokew(0x0000, 0x01D2, old_mouseInt_seg);
    
    asm("sti");
}

/**
    Mouse interrupt handler
    This function is not to be called directly.
*/
void mouseInterruptHandler(void) {
    asm("pusha \n"
        "push ds \n"
        "mov ax, 0x3000 \n"
        "mov ds, ax");
        
    char number = 0;
        
    // Abort if no mouse data is available
    if (inb(PS2_STATUS_PORT) & 32) goto finish;
    
    // Parse the data in accordance to the byte number
    if (number == 0) {
        // Byte contains status flags for buttons and such
        mouse_data = inb(PS2_DATA_PORT);
        number++; // The next byte will be X-delta
        
    } else if (number == 1) {
        // Byte contains X-delta, AKA left-right mouse movement
        mouse_dx = inb(PS2_DATA_PORT);
        number++; // The next byte will be Y-delta
        
    } else {
        // Byte contains Y-delta, AKA up-down mouse movement
        mouse_dy = inb(PS2_DATA_PORT);
        number = 0; // The next byte will be data flags
        
        /*** Process the full mouse packet ***/
        
            // If x- or y-overflow is set, ignore the entire packet
            if (mouse_data & 0x00C0) goto finish;
        
            mouse_changed = true;
            
            /*** Calculate DX ***/
            
                if (mouse_data & 16) {
                    /*** Negative DX ***/
                    
                    // Left movement - invert dx and substract it from rawX
                    char inverted_dx = (mouse_dx ^ 0xFF) + 1;
                    if (inverted_dx <= mouse_rawX) mouse_rawX -= inverted_dx;
                    else mouse_rawX = 0;
                    
                } else {
                    /*** Positive DX ***/
                    
                    // Right movement - add dx to rawX
                    mouse_rawX += mouse_dx;
                }
            
            /*** Scale X ***/
                
                // Shift rawX in accordance to the mouse scale factor to find the 'scaled' position
                // Mouse position is based on the raw position, but functions read the scaled position
                mouse_posX = mouse_rawX >> mouse_scaleX;
            
            /*** Check X boundaries ***/
                
                // Ensure the new scaled position does not exceed the boundaries set by the program
                if (mouse_posX < mouse_minX) {
                    mouse_posX = mouse_minX;
                    
                    // Reverse the shift to find the corresponding raw position, because that's the one that gets updated
                    mouse_rawX = mouse_posX << mouse_scaleX;
                }
                else if (mouse_posX > mouse_limX) {
                    mouse_posX = mouse_limX;
                    
                    mouse_rawX = mouse_posX << mouse_scaleX;
                }
            
            /*** Calculate DY ***/
            
                if (mouse_data & 32) {
                    /*** Negative DY ***/
                    
                    // Down movement - invert dy and add it to rawY
                    mouse_rawY += (mouse_dy ^ 0xFF) + 1;
                    
                } else {
                    /*** Positive DY***/
                    
                    // Up movement - subtract dy from rawY
                    if (mouse_dy > mouse_rawY) mouse_rawY = 0;
                    else mouse_rawY -= mouse_dy;
                }
                
            /*** Scale Y ***/
            
                mouse_posY = mouse_rawY >> mouse_scaleY;
                
            /*** Check Y boundaries ***/
                
                if (mouse_posY < mouse_minY) {
                    mouse_posY = mouse_minY;
                    
                    mouse_rawY = mouse_posY << mouse_scaleY;
                    
                } else if (mouse_posY > mouse_limY) {
                    mouse_posY = mouse_limY;
                    
                    mouse_rawY = mouse_posY << mouse_scaleY;
                }
                
            /*** Check buttons ***/
            
            // TODO
    }
    
    finish:
        // For IRQ 8-15 we MUST send an End Of Interrupt command to both the master and slave PIC
        // Otherwise, no more interrupts will be sent the mouse and keyboard will be locked up
        outb(0x20, 0x20);
        outb(0xA0, 0x20);
        
        asm("pop ds \n"
            "popa \n"
            "iret");
}
