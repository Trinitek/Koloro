
; TachyonOS Mouse Interupt Handler
; Copyright (c) 2013 TachyonOS Developers

_mouse_int_handler:
    pusha
	push ds
	mov ax, 0x2000
	mov ds, ax
	
	; Check that data is available for the mouse
	in al, 0x64
	bt ax, 5
	jnc .finish
	
	; Check which byte number this is 
	cmp byte [.number], 0
	je .data_byte
	
	cmp byte [.number], 1
	je .x_byte
	
	cmp byte [.number], 2
	je .y_byte

.data_byte:
	; Collect data byte - contains buttons, overflow flags, alignment bit and negative delta flags
	in al, 0x60
	mov [mouselib_int_data], al
	
	; The next byte will be X-delta
	mov byte [.number], 1
	jmp .finish
	
.alignment:
	mov byte [.number], 0
	jmp .finish
 	
.x_byte:
	; Collect X-delta byte - contains left-right mouse movement
	in al, 0x60
	mov [mouselib_int_delta_x], al
	; The next byte will be Y-delta
	mov byte [.number], 2
	jmp .finish
	
.y_byte:
	; Collect Y-delta byte - contains up-down mouse movement
	in al, 0x60
	mov [mouselib_int_delta_y], al
	; The next byte will byte the data byte
	mov byte [.number], 0

; Now we have the entire packet it is time to process its data.
; We want to figure out the new X and Y co-ordinents and which buttons are pressed.
	
.process_packet:
	mov ax, 0
	mov bx, 0
	mov bl, [mouselib_int_data]
	test bx, 0x00C0			; If x-overflow or y-overflow is set ignore packet
	jnz .finish

	mov byte [mouselib_int_changed], 1 	; Mark there has been a mouse update for functions awaiting mouse input
	
	; Get the movement values
	mov cx, 0
	mov cl, [mouselib_int_delta_x]
	mov dx, 0
	mov dl, [mouselib_int_delta_y]
	
	; Check data byte for the X sign flag
	bt bx, 4
	jc .negative_delta_x

	; Right Movement - Add the X-delta to the raw X position
	add [mouselib_int_x_raw], cx
	jmp .scale_x
	
.negative_delta_x:
	; Left movement - Invert the X-delta and subtract it from the raw X position
	xor cl, 0xFF
	inc cl

	; Verify that the number to be subtract is greater than the total to avoid an underflow.
	cmp cx, [mouselib_int_x_raw]
	jg .zero_x
	
	sub [mouselib_int_x_raw], cx
	
.scale_x:
	; We have the new 'raw' position
	; Now shift it according to the mouse scale factor to find the 'scaled' position
	; The mouse position is based of the raw position but functions read the scaled position
	mov cx, [mouselib_int_x_raw]
	
	mov ax, cx
	mov cl, [mouselib_int_x_scale]
	shr ax, cl
	mov cx, ax
	mov [mouselib_int_x_position], cx
	
.check_x_boundries:
	; Make sure the new scaled position does not exceed the boundries set by the operating system
	cmp cx, [mouselib_int_x_minimum]
	jl .fix_x_minimum
	
	cmp cx, [mouselib_int_x_limit]
	jg .fix_x_limit
	
.find_y_position:
	; Now do everything again to process the Y-delta
	bt bx, 5			; Check data byte for the Y sign flag
	jc .negative_delta_y
	
	cmp dx, [mouselib_int_y_raw]
	jg .zero_y
	
	; Upward movememnt, take Y-delta from the raw Y position
	sub [mouselib_int_y_raw], dx
	jmp .scale_y
	
.negative_delta_y:
	; Downward movement, invert Y-delta and add it to the raw Y position
	xor dl, 0xFF
	inc dl
		
	add [mouselib_int_y_raw], dx
	
.scale_y:
	mov dx, [mouselib_int_y_raw]
	
	mov cl, [mouselib_int_y_scale]
	shr dx, cl
	mov [mouselib_int_y_position], dx
	
.check_y_boundries:
	cmp dx, [mouselib_int_y_minimum]
	jl .fix_y_minimum
	
	cmp dx, [mouselib_int_y_limit]
	jg .fix_y_limit
	
.check_buttons:
	; Movement is complete, now to update the button press status
	; These can be taken from the lower bits of data byte
	; Bit 0 = Left Mouse
	; Bit 1 = Right Mouse
	; Bit 2 = Middle Mouse
	
	bt bx, 0
	jc .left_mouse_pressed
	
	mov byte [mouselib_int_button_left], 0		; If a button is not pressed, set it's status to zero
	
	bt bx, 2
	jc .middle_mouse_pressed
	
	mov byte [mouselib_int_button_middle], 0
	
	bt bx, 1
	jc .right_mouse_pressed
	
	mov byte [mouselib_int_button_right], 0
	
.finish:
	; For IRQ 8-15 we MUST send and End Of Interrupt command to both the master and slave PIC
	; Otherwise we will not get any more interrupts and lockup our mouse and keyboard
	mov al, 0x20				; End Of Interrupt (EOI) command
	out 0x20, al				; Send EOI to master PIC
	out 0xa0, al				; Send EOI to slave PIC
	
	; And that's all for now
	pop ds
	popa
	iret
	
	.number				db 0
    