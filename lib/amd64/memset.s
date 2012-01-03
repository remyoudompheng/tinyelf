// fill(long *dest, long value, long length)
.global fill
fill:
        mov %rsi, %rax
        mov %rdx, %rcx
        rep stosq
        ret

