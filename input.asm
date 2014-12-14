bits 16

; glb getKey : (void) char
_getKey:
	push	bp
	mov	bp, sp
	jmp	L201
L200:
mov ah, 0x10
int 0x16

L202:
	leave
	ret
L201:
	jmp	L200
; glb waitForKey : (void) void
_waitForKey:
	push	bp
	mov	bp, sp
	jmp	L205
L204:
; while
; RPN'ized expression: "( getKey ) 0 == "
; Expanded expression: " getKey ()0 0 == "
L208:
; Fused expression:    "( getKey )0 == ax 0 IF! "
	call	_getKey
	cmp	ax, 0
	jne	L209
	jmp	L208
L209:
L206:
	leave
	ret
L205:
	jmp	L204

; Syntax/declaration table/stack:
; Bytes used: 168/20736


; Macro table:
; Macro __SMALLER_C__ = `0x0100`
; Macro __SMALLER_C_16__ = ``
; Macro __SMALLER_C_SCHAR__ = ``
; Bytes used: 63/4096


; Identifier table:
; Ident getKey
; Ident <something>
; Ident waitForKey
; Bytes used: 33/4752

; Next label number: 210
; Compilation succeeded.
