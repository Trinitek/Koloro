
    org 32768
    
start:
    jmp .main                   ; 0
    
    buffer_ofs      dw buffer   ; 2
    proc_load_file:             ; 4
        call load_file
        retf
    proc_save_file:             ; 8
        call save_file
        retf
    
    start.main:
    jmp main

; Load a file from disk
; 
; @param
;   SI - pointer to null-terminated filename
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
    lodsb
    stosb
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
    ret

; Save a file to disk
;
; @param
;   SI - pointer to null-terminated filename
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
    lodsb
    stosb
    cmp al, 0
    jnz .getChar
    
    push ax
    mov ax, 0x2000
    mov ds, ax
    mov fs, ax
    mov gs, ax
    pop ax
    
    call 0x0090
    mov si, filename_str
    call 0x0003
    
    mov ax, filename_str
    mov bx, buffer
    call 0x0096
    
    pop gs
    pop fs
    pop es
    pop ds
    ret
    
main:
    ; Number of bytes to copy
    mov cx, 32768-buffer
    
    ; Setup the destination to be directly above current segment
    mov ax, 0x2000+4096
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

;filename_str db 13 dup (0)
filename_str db "FORCE.TXT",0
    
buffer: