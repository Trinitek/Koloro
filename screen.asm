bits 16

org 0x100
; glb getKey : (void) char
_getKey:
	push	bp
	mov	bp, sp
	jmp	L2
L1:
mov ah, 0x10
int 0x16

L3:
	leave
	ret
L2:
	jmp	L1
; glb waitForKey : (void) void
_waitForKey:
	push	bp
	mov	bp, sp
	jmp	L6
L5:
; while
; RPN'ized expression: "( getKey ) 0 == "
; Expanded expression: " getKey ()0 0 == "
L9:
; Fused expression:    "( getKey )0 == ax 0 IF! "
	call	_getKey
	cmp	ax, 0
	jne	L10
	jmp	L9
L10:
L7:
	leave
	ret
L6:
	jmp	L5
; glb main : (void) void
_main:
	push	bp
	mov	bp, sp
	jmp	L12
L11:
; RPN'ized expression: "( 19 setMode ) "
; Expanded expression: " 19  setMode ()2 "
; Fused expression:    "( 19 , setMode )2 "
	push	19
	call	_setMode
	sub	sp, -2
; RPN'ized expression: "( 8 , 0 , 0 putPixel ) "
; Expanded expression: " 8  0  0  putPixel ()6 "
; Fused expression:    "( 8 , 0 , 0 , putPixel )6 "
	push	8
	push	0
	push	0
	call	_putPixel
	sub	sp, -6
; RPN'ized expression: "( waitForKey ) "
; Expanded expression: " waitForKey ()0 "
; Fused expression:    "( waitForKey )0 "
	call	_waitForKey
; return
	jmp	L13
; Fused expression:    "0 "
	mov	ax, 0
L13:
	leave
	ret
L12:
	jmp	L11
; glb putPixel : (
; prm     x : unsigned
; prm     y : unsigned
; prm     color : char
;     ) void
_putPixel:
	push	bp
	mov	bp, sp
	jmp	L16
L15:
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
L17:
	leave
	ret
L16:
	jmp	L15
; glb putPixelOfs : (
; prm     offset : int
; prm     color : char
;     ) void
_putPixelOfs:
	push	bp
	mov	bp, sp
	jmp	L20
L19:
; loc     offset : (@4): int
; loc     color : (@6): char
mov bx, [bp + 4]
mov ax, [bp + 6]
mov cx, 0xA000
mov ds, cx
mov [ds:bx], al

L21:
	leave
	ret
L20:
	jmp	L19
; glb setMode : (
; prm     mode : char
;     ) void
_setMode:
	push	bp
	mov	bp, sp
	jmp	L24
L23:
; loc     mode : (@4): char
mov ax, [bp + 4]
mov ah, 0
int 0x10
L25:
	leave
	ret
L24:
	jmp	L23

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
; Ident main
; Ident putPixel
; Ident x
; Ident y
; Ident color
; Ident putPixelOfs
; Ident offset
; Ident setMode
; Ident mode
; Bytes used: 98/4752

; Next label number: 27
; Compilation succeeded.
