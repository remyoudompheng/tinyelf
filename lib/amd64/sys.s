.text

.globl read
read:
        // fd in %edi, data in %rsi, data_len in %edx
        movl $0, %eax
        syscall
        ret

// write(int fd, char *data, int data_len)
.globl write
write:
        // fd in %edi, data in %rsi, data_len in %edx
        movl $1, %eax
        syscall
        ret

.globl ioctl
ioctl:
        movl $16, %eax
        syscall
        ret

// exit(int code)
.globl exit
exit:
        mov $231, %eax
        syscall

