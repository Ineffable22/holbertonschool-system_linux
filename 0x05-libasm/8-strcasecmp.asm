BITS 64
	global	asm_strcasecmp

asm_strcasecmp:
	push	rbp
	mov	rbp, rsp

compare:
	mov	al, byte [rdi]
	mov	dl, byte [rsi]
	cmp	al, 0x0
	je	success
	cmp	al, dl
	jne	is_alpha

increment:
	inc	rdi
	inc	rsi
	jmp	compare

is_alpha:
	cmp	al, 0x41
	jl	fail
	cmp	al, 0x5A
	jle	upper
	cmp	al, 0x61
	jl	fail
	cmp	al, 0x7A
	jle	lower
	jmp	fail

fail:
	sub	al, dl
	jmp	end

upper:
	sub	al, dl
	cmp	al, -0x20
	je	increment
	jmp	end

lower:
	sub	al, dl
	cmp	al, 0x20
	je	increment
	jmp	end

success:
	cmp	dl, 0x0
	je	end
	mov	al, dl

end:
	mov	rsp, rbp
	pop	rbp
	ret
