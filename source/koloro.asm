
; This is the file that is assembled in order to produce the final KOLORO.BIN binary

; Loader, assembled separately with FASM
incbin 'loader.bin'

; Include any SmallerC-compiled sources here
%include 'main.asm'     ; This must be first in the list!
%include 'input.asm'
%include 'screen.asm'
%include 'system.asm'
%include 'draw.asm'
%include 'file.asm'
%include 'math.asm'
%include 'fixed.asm'
;%include 'state.asm'

; Additional constant definitions, etc.
%include '../source/mikedev.inc'