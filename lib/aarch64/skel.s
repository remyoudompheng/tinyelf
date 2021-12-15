.text
.globl _start

_start:
        bl main // returns to x0
        mov x8, 94 // SYS_exit_group
        svc 0
