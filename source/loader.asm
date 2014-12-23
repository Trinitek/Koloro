
    org 32768
    
start:
    jmp .main
    
    buffer_ofs      dw buffer
    load_file_ptr   dw load_file
    save_file_ptr   dw save_file
    
    start.main:
    jmp main

; Load a file from disk
; 
; @param
;   AX - pointer to null-terminated filename
; @return
;   BX - file size in bytes
;   CARRY - set if error
load_file:
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x2000
    mov es, ax
    mov di, filename_str
    
    .getChar:
    movsb
    cmp al, 0
    jnz .getChar
    
    mov ax, 0x2000
    mov ds, ax
    mov fs, ax
    mov gs, ax
    
    mov ax, filename_str
    mov cx, buffer
    call 0x0021
    
    pop gs
    pop fs
    pop es
    pop ds
    retf

; Save a file to disk
;
; @param
;   AX - pointer to null-terminated filename
;   CX - number of bytes to save
; @return
;   CARRY - set if error
save_file:
    push ds
    push es
    push fs
    push gs
    
    mov ax, 0x2000
    mov es, ax
    mov di, filename_str
    
    .getChar:
    movsb
    cmp al, 0
    jnz .getChar
    
    mov ax, 0x2000
    mov ds, ax
    mov fs, ax
    mov gs, ax
    
    mov ax, filename_str
    mov bx, buffer
    call 0x0096
    
    pop gs
    pop fs
    pop es
    pop ds
    retf
    
main:
    ; Number of bytes to copy
    mov cx, 32768-buffer
    
    ; Setup the destination to be directly above current segment
    mov ax, 0x2000
    add ax, 4096
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
    call 0x2000+4096:0
    
    ; Restore all segment registers before returning
    mov ax, 0x2000
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Return to operating system
    ret

filename_str db 13 dup 0
    
buffer: