
BITS 64

SECTION .text

main:
	push rax
	push rcx
	push rdx
	push rsi
	push rdi
	push r11
	
	mov rax, 1
	mov rdi, 1
	lea rsi, [rel $+hello-$]
	mov rdx, 13
	syscall

	pop r11
	pop rdi
	pop rsi
	pop rdx
 	pop rcx
	pop rax
	push  0x11c0
	ret

hello: db "Hello world", 33, 10




