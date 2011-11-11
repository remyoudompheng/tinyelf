.text
.globl write

// write(int fd, char *data, int data_len)
write:
        movl $4, %eax
        movl 4(%esp), %ebx
        movl 8(%esp), %ecx
        movl 12(%esp), %edx
        int $0x80
        ret
