BITS 64
	global	asm_memcpy

asm_memcpy:
	push	rbp
	mov	rbp, rsp
	push	rax

loop:
	cmp	dl, 0x0
	je	end
	mov	al, byte [rsi]
	mov	byte [rdi], al
	inc	rdi
	inc	rsi
	dec	rdx
	jmp	loop

end:
	pop	rax
	mov	rsp, rbp
	pop	rbp
	ret
