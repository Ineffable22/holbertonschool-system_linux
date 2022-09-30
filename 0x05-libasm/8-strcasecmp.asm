BITS 64
	global	asm_strcasecmp

asm_strcasecmp:
	push	rbp
	mov	rbp, rsp

compare:
	movzx	eax, byte [rdi]
	movzx	ecx, byte [rdi]
	movzx	edx, byte [rsi]

	cmp	al, 0x0
	je	success
	cmp	al, dl
	je	increment

	sub	cl, dl
	cmp	al, 0x41
	jl	fail
	cmp	al, 0x5A
	jle	upper
	cmp	al, 0x61
	jl	fail
	cmp	al, 0x7A
	jle	lower
	jmp	fail

increment:
	inc	rdi
	inc	rsi
	jmp	compare

fail:
	cmp	al, dl
	jl	less
	mov	al, cl
	jmp	end

less:
	mov	al, cl
	neg	al
	imul	eax, -1
	jmp	end

upper:
	cmp	cl, -0x20
	je	increment
	jmp	fail

lower:
	cmp	cl, 0x20
	je	increment
	jmp	fail

success:
	cmp	dl, 0x0
	je	end
	mov	al, dl

end:
	mov	rsp, rbp
	pop	rbp
	ret
