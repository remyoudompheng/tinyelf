.text

.globl read
read:
        movl $3, %eax
        movl 4(%esp), %ebx
        movl 8(%esp), %ecx
        movl 12(%esp), %edx
        int $0x80
        ret

// write(int fd, char *data, int data_len)
.globl write
write:
        movl $4, %eax
        movl 4(%esp), %ebx
        movl 8(%esp), %ecx
        movl 12(%esp), %edx
        int $0x80
        ret

// ioctl(int fd, int cmd, void *args);
.globl ioctl
ioctl:
        movl $0x36, %eax
        movl 4(%esp), %ebx
        movl 8(%esp), %ecx
        movl 12(%esp), %edx
        int $0x80
        ret

// exit(int code)
.globl exit
exit:
        mov $0xfc, %eax
        movl 4(%esp), %ebx
        int $0x80
        ret

