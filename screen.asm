bits 16

org 0x100
; glb putPixel : (
; prm     x : unsigned
; prm     y : unsigned
; prm     color : char
;     ) void
_putPixel:
	push	bp
	mov	bp, sp
	jmp	L101
L100:
; loc     x : (@4): unsigned
; loc     y : (@6): unsigned
; loc     color : (@8): char
; RPN'ized expression: "( color , y 200 * x + putPixelOfs ) "
; Expanded expression: " (@8) *(-1)  (@6) *(2) 200 * (@4) *(2) +  putPixelOfs ()4 "
; Fused expression:    "( *(-1) (@8) , * *(@6) 200 + ax *(@4) , putPixelOfs )4 "
	mov	al, [bp+8]
	cbw
	push	ax
	mov	ax, [bp+6]
	imul	ax, ax, 200
	add	ax, [bp+4]
	push	ax
	call	_putPixelOfs
	sub	sp, -4
L102:
	leave
	ret
L101:
	jmp	L100
; glb putPixelOfs : (
; prm     offset : int
; prm     color : char
;     ) void
_putPixelOfs:
	push	bp
	mov	bp, sp
	jmp	L105
L104:
; loc     offset : (@4): int
; loc     color : (@6): char
mov bx, [bp + 4]
mov ax, [bp + 6]
mov cx, 0xA000
mov ds, cx
mov [ds:bx], al

L106:
	leave
	ret
L105:
	jmp	L104
; glb setMode : (
; prm     mode : char
;     ) void
_setMode:
	push	bp
	mov	bp, sp
	jmp	L109
L108:
; loc     mode : (@4): char
mov ax, [bp + 4]
mov ah, 0
int 0x10
L110:
	leave
	ret
L109:
	jmp	L108

; Syntax/declaration table/stack:
; Bytes used: 264/20736


; Macro table:
; Macro __SMALLER_C__ = `0x0100`
; Macro __SMALLER_C_16__ = ``
; Macro __SMALLER_C_SCHAR__ = ``
; Bytes used: 63/4096


; Identifier table:
; Ident putPixel
; Ident x
; Ident y
; Ident color
; Ident putPixelOfs
; Ident offset
; Ident setMode
; Ident mode
; Bytes used: 59/4752

; Next label number: 112
; Compilation succeeded.
