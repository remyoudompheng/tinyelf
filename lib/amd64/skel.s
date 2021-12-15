.text
.globl _start

_start:
        call main
        mov %rax, %rdi
        mov $231, %eax
        syscall

