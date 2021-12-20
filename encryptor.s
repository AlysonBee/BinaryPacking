
section .data
target: db "Hello world", 0

section .text
global main:

main:
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	push r11
	
	;mov rax, target
	xor rcx, rcx
	push rax 

loop:
	cmp byte[rax + rcx], 0
	je printout
	mov bl, byte[rax + rcx]
	;inc bl
	xor bl, 42
	mov byte[rax + rcx], bl

	inc rax
	jmp loop


printout:
	mov rax, 1
	mov rdi, 1
	pop rsi
	mov rdx, 13
	syscall

	mov rax, 60
	syscall

	pop r11
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax




