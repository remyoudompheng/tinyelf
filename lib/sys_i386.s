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

// select(int n, void *read_fds, void *write_fds, void *err_fds, void *tv)
.globl select
select:
        movl $142, %eax
        movl 4(%esp), %ebx
        movl 8(%esp), %ecx
        movl 12(%esp), %edx
        movl 16(%esp), %esi
        movl 20(%esp), %edi
        int $0x80
        ret

// nanosleep(timespec *t, timespec *rem)
.globl nanosleep
nanosleep:
        movl $162, %eax
        movl 4(%esp), %ebx
        movl 8(%esp), %ecx
        int $0x80
        ret
