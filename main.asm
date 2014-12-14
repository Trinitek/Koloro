bits 16

org 32768
; glb getKey : (void) char
; glb waitForKey : (void) void
; glb putPixel : (
; prm     x : unsigned
; prm     y : unsigned
; prm     color : char
;     ) void
; glb putPixelOfs : (
; prm     offset : int
; prm     color : char
;     ) void
; glb setMode : (
; prm     mode : char
;     ) void
; glb main : (void) void
_main:
	push	bp
	mov	bp, sp
	jmp	L2
L1:
; RPN'ized expression: "( 19 setMode ) "
; Expanded expression: " 19  setMode ()2 "
; Fused expression:    "( 19 , setMode )2 "
	push	19
	call	_setMode
	sub	sp, -2
; RPN'ized expression: "( 12 , 0 , 0 putPixel ) "
; Expanded expression: " 12  0  0  putPixel ()6 "
; Fused expression:    "( 12 , 0 , 0 , putPixel )6 "
	push	12
	push	0
	push	0
	call	_putPixel
	sub	sp, -6
; RPN'ized expression: "( waitForKey ) "
; Expanded expression: " waitForKey ()0 "
; Fused expression:    "( waitForKey )0 "
	call	_waitForKey
; RPN'ized expression: "( 3 setMode ) "
; Expanded expression: " 3  setMode ()2 "
; Fused expression:    "( 3 , setMode )2 "
	push	3
	call	_setMode
	sub	sp, -2
; return
	jmp	L3
; Fused expression:    "0 "
	mov	ax, 0
L3:
	leave
	ret
L2:
	jmp	L1
%include 'input.asm'
%include 'screen.asm'

; Syntax/declaration table/stack:
; Bytes used: 408/20736


; Macro table:
; Macro __SMALLER_C__ = `0x0100`
; Macro __SMALLER_C_16__ = ``
; Macro __SMALLER_C_SCHAR__ = ``
; Bytes used: 63/4096


; Identifier table:
; Ident getKey
; Ident <something>
; Ident waitForKey
; Ident putPixel
; Ident x
; Ident y
; Ident color
; Ident putPixelOfs
; Ident offset
; Ident setMode
; Ident mode
; Ident main
; Bytes used: 98/4752

; Next label number: 5
; Compilation succeeded.
