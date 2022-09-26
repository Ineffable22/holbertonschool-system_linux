BITS 64
	global	asm_strchr

asm_strchr:
	push	rbp
	mov	rbp, rsp
	mov	rax, 0x0

loop:
	cmp	byte [rdi], sil
	je	success
	cmp	byte [rdi], 0x0
	je	end
	inc	rdi
	jmp	loop

success:
	mov	rax, rdi

end:
	mov	rsp, rbp
	pop	rbp
	ret
