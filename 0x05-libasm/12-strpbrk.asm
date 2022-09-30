BITS 64
        global  asm_strpbrk

asm_strpbrk:
        push    rbp
        mov     rbp, rsp
	mov     rcx, rsi
	mov	rax, 0x0

loop:
        movzx   edx, byte[rdi]
        cmp     dl, 0x0
        je      end
        cmp     byte [rsi], 0x0
        je      next
        cmp     dl, byte [rsi]
        je      found
        inc     rsi
        jmp     loop

next:
        inc     rdi
        mov     rsi, rcx
        jmp     loop

found:
	mov	rax, rdi

end:
        mov     rsp, rbp
        pop     rbp
        ret
