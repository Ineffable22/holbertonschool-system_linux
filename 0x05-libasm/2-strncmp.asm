BITS 64
	global	asm_strncmp

asm_strncmp:
	push	rbp
	mov	rbp, rsp
	push	rcx

loop:
	movzx 	eax, byte [rdi]
	movzx 	ecx, byte [rsi]
	cmp	al, 0x0
	je	compare
	cmp	al, cl
	jne	compare
	inc	rdi
	inc	rsi
	dec	edx
	jz	success
	jmp	loop

greater:
	sub     al, cl
	jmp	end

less:
	sub	al, cl
	sub	rax, 256
	jmp	end

compare:
	cmp	al, cl
	jg	greater
	jl	less

success:
	mov	rax, 0x0

end:
	pop	rcx
	mov	rsp, rbp
	pop	rbp
	ret
