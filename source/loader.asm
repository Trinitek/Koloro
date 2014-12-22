
    org 32768
    
start:
    ; Number of bytes to copy
    mov cx, 32768-buffer
    
    ; Setup the destination to be directly above current segment
    mov ax, 0x2000
    add ax, 4096
    mov es, ax
    xor di, di
    mov si, buffer
    
    ; Copy!
    rep movsb
    
    ; Setup segment registers for program
    mov ds, ax
    mov fs, ax
    mov gs, ax
    
    ; Far call!
    call 0x2000:0
    ret
    
buffer: