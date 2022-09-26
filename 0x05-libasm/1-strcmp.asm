BITS 64
	global	asm_strcmp

asm_strcmp:
	push	rbp
	mov	rbp, rsp
	push	rdx

loop:
	mov	rax, rdi
	mov	rdx, rsi
	movzx 	eax, byte [rax]
	movzx 	edx, byte [rdx]
	cmp	al, dl
	jg	greater
	jl	less
	inc	rdi
	inc	rsi
	jmp	loop

greater:
	mov	rax, 0x1
	jmp	end

less:
	mov	rax, -0x1
	jmp	end

compare:
	cmp	al, dl
	jg	greater
	jl	less
	mov	rax, 0x0

end:
	pop	rdx
	mov	rsp, rbp
	pop	rbp
	ret
