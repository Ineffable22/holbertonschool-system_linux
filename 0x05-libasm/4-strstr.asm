BITS 64
	global	asm_strstr

asm_strstr:
	push	rbp
	mov	rbp, rsp
	movzx	ecx, byte [rsi]
	cmp	cl, 0x0
	je	haystack

loop:
	movzx	edx, byte [rdi]
	movzx	ecx, byte [rsi]
	cmp	dl, 0x0
	je	fail
	cmp	dl, cl
	je	send
	inc	rdi
	jmp	loop

send:
	mov	rdx, rdi
	mov	rcx, rsi

loop2:
	movzx	eax, byte [rdi]
	movzx	ebx, byte [rsi]
	cmp	al, 0x0
	je	validate
	cmp	bl, 0x0
	je	validate
	cmp	al, bl
	jne	retrn
	inc	rdi
	inc	rsi
	jmp	loop2

retrn:
	mov	rdi, rdx
	mov	rsi, rcx
	inc	rdi
	jmp	loop

haystack:
	mov	rax, rdi
	jmp	end

validate:
	mov	rax, rdx
	jmp	end

fail:
	mov	rax, 0x0

end:
	mov	rsp, rbp
	pop	rbp
	ret
