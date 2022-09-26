BITS 64

	global	asm_strlen

asm_strlen:
	push	rbp
	mov	rbp, rsp
	mov	rax, 0x0

loop:
	cmp	byte [rdi], 0x0
	je	end
	inc	rax
	inc	rdi
	jmp	loop

end:
	mov	rsp, rbp
	pop	rbp
	ret
