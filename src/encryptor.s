BITS 64


SECTION .text
global main

main:
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push r11

	xor rcx, rcx


loop:
	cmp rcx,3103
	je printout
	mov al, [0x4007b0+rcx]
	xor al, 42
	mov [0x4007b0+rcx], al
	inc rcx
	jmp loop

printout:
	pop r11
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
;	mov rax, 60
;	syscall
	push 0x4007b0
	ret


