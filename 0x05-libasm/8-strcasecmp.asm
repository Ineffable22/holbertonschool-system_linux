BITS 64
	global	asm_strcasecmp

asm_strcasecmp:
	push	rbp
	mov	rbp, rsp

compare:
	movzx	eax, byte [rdi]
	movzx	edx, byte [rsi]

	cmp	al, 0x0
	jne	first
	cmp	dl, 0x0
	je	fail

first:
	cmp	al, 0x41
	jl	second
	cmp	al, 0x5A
	jg	second
	add	ax, 0x20

second:
	cmp	dl, 0x41
	jl	increment
	cmp	dl, 0x5A
	jg	increment
	add	dx, 0x20

increment:
	cmp	al, dl
	jne	fail
	inc	rdi
	inc	rsi
	jmp	compare

fail:
	cmp	al, dl
	jl	less
	je	success
	sub	al, dl
	jmp	end

less:
	sub	al, dl
	neg	al
	imul	eax, -1
	jmp	end

success:
	mov	rax, 0x0
	je	end

end:
	mov	rsp, rbp
	pop	rbp
	ret
