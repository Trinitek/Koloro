
; This is the file that is assembled in order to produce the final KOLORO.BIN binary

; Loader, assembled separately with FASM
incbin 'loader.bin'

; Program, assembled separately with NASM
incbin 'prog.bin'
