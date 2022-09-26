BITS 64
	global	asm_strcmp

asm_strcmp:
	push	rbp
	mov	rbp, rsp
	push	rdx

loop:
	movzx 	eax, byte [rdi]
	movzx 	edx, byte [rsi]
	cmp	al, 0x0
	je	compare
	cmp	al, dl
	jne	compare
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
