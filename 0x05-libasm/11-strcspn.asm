BITS 64
        global  asm_strcspn

asm_strcspn:
        push    rbp
        mov     rbp, rsp
        mov     rax, 0x0
        mov     rcx, rsi

loop:
        movzx   edx, byte[rdi]
        cmp     dl, 0x0
        je      end
        cmp     byte [rsi], 0x0
        je      found
        cmp     dl, byte [rsi]
        je      end
        inc     rsi
        jmp     loop

found:
        inc     rax
        inc     rdi
        mov     rsi, rcx
        jmp     loop

end:
        mov     rsp, rbp
        pop     rbp
        ret
