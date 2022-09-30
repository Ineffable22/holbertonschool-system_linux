BITS 64
        global  asm_strncasecmp

asm_strncasecmp:
        push    rbp
        mov     rbp, rsp

compare:
	cmp	rdx, 0x0
	je	fail
        movzx   eax, byte [rdi]
        movzx   ecx, byte [rsi]

        cmp     al, 0x0
        jne     first
        cmp     cl, 0x0
        je      fail

first:
        cmp     al, 0x41
        jl      second
        cmp     al, 0x5A
        jg      second
        add     ax, 0x20

second:
        cmp     cl, 0x41
        jl      increment
        cmp     cl, 0x5A
        jg      increment
        add     cx, 0x20

increment:
        cmp     al, cl
        jne     fail
        inc     rdi
        inc     rsi
	dec	rdx
        jmp     compare

fail:
        cmp     al, cl
        jl      less
        je      success
        sub     al, cl
        jmp     end

less:
        sub     al, cl
        neg     al
        imul    eax, -1
        jmp     end

success:
        mov     rax, 0x0

end:
        mov     rsp, rbp
        pop     rbp
        ret
