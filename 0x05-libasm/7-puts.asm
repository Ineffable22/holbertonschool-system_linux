BITS 64
	global	asm_puts
	extern	asm_strlen

asm_puts:
	push	rbp
	mov	rbp, rsp

printer:
	push	rdi
	call	asm_strlen
	pop	rdi
	mov	rcx, rax
	push	rdi
	mov	rax, 1
	mov	rdi, 1
	mov	rsi, [rsp]
	mov	rdx, rcx
	syscall

end:
	pop	rdi
	mov	rax, rcx
	mov	rsp, rbp
	pop	rbp
