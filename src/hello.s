
BITS 64

SECTION .text
global main

main:
	push rax
	push rcx
	push rdx
	push rsi
	push rdi

	mov rax, 1
	mov rdi, 1
	lea rsi, [rel hello-$]
	mov rdx, [rel $+len-$]
	syscall
	
	pop rdi
	pop rsi
	pop rdx
 	pop rcx
	pop rax
	
	ret


hello: db "Hello world", 33, 10
len:   dd 13



