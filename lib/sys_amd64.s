.text
.globl write

// write(int fd, char *data, int data_len)
write:
        // Linux amd64
        movl $1, %eax
        movl 8(%esp), %edi
        movq 16(%esp), %esi
        movl 24(%esp), %edx
        int $0x80
        ret
