.text
.globl write

// write(int fd, char *data, int data_len)
write:
        // fd in %edi, data in %rsi, data_len in %edx
        movl $1, %eax
        syscall
        ret
