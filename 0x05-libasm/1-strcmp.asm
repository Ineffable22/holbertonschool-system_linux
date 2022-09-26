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
	cmp	al, 0x0
	je	success
	cmp	al, dl
	jne	noequal
	inc	rdi
	inc	rsi
	jmp	loop

noequal:
	jl	less

greater:
	mov	rax, 0x1
	jmp	end

less:
	mov	rax, -0x1
	jmp	end

success:
	mov	rax, 0x0

end:
	pop	rdx
	mov	rsp, rbp
	pop	rbp
	ret
