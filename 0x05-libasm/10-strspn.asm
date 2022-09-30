BITS 64
        global  asm_strspn

asm_strspn:
        push    rbp
        mov     rbp, rsp
	mov	rax, 0x0
	mov	rcx, rsi

loop:
	movzx	edx, byte[rdi]
	cmp	dl, 0x0
	je	end
	cmp	byte [rsi], 0x0
	je	end
	cmp	dl, byte [rsi]
	je	found
	inc	rsi
	jmp	loop

found:
	inc	rax
	inc	rdi
	mov	rsi, rcx
	jmp	loop

end:
        mov     rsp, rbp
        pop     rbp
        ret
