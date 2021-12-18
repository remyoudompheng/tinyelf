.text
.globl _start

_start:
        call main
        mov %rax, %rdi
        call exit

