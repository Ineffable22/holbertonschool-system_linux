BITS 64
	global	asm_putc

asm_putc:
	push	rbp
	mov	rbp, rsp
	
print:
	push	rdi
	mov	rax, 1
	mov	rdi, 1
	mov	rsi, rsp
	mov	rdx, 1
	syscall

end:
	mov	rsp, rbp
	pop	rbp
	ret
