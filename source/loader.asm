
buffer_ofs equ 32768 + 256

macro pushseg {
    push ds
    push es
    push fs
    push gs
}

macro popseg {
    pop gs
    pop fs
    pop es
    pop ds
}

    org 32768
    
start:
    jmp .main                   ; 0
    
    proc_load_file:             ; 2
        call load_file
        retf
    proc_save_file:             ; 6
        call save_file
        retf
    proc_print_string:          ; 10
        call print_string
        retf
    
    start.main:
    jmp main

; Load a file from disk
;
; @return
;   BX - file size in bytes
;   CARRY - set if error
load_file:
    pushseg
    
    mov ax, 0x2000
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ax, buffer_ofs
    mov cx, buffer_ofs
    call 0x0021
    
    popseg
    ret

; Save a file to disk
;
; @param
;   CX - number of bytes to save
; @return
;   CARRY - set if error
save_file:
    pushseg
    
    mov ax, 0x2000
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ax, buffer_ofs
    call 0x0096
    
    popseg
    ret

print_string:
    pushseg
    
    mov ax, 0x2000
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call 0x0003
    
    popseg
    ret
    
main:
    ; Number of bytes to copy
    mov cx, 32768-buffer
    
    ; Setup the destination to be directly above current segment
    mov ax, 0x3000
    mov es, ax
    xor di, di
    mov si, buffer
    
    ; Copy
    rep movsb
    
    ; Setup segment registers for program before calling
    mov ds, ax
    mov fs, ax
    mov gs, ax
    
    ; Far call to the executable
    call 0x3000:0;+13
    
    ; Restore all segment registers before returning
    mov ax, 0x2000
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Return to operating system
    ret
   
buffer:
