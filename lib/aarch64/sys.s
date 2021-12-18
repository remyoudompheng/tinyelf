.text

.globl read
read:
        mov x8, 0x3f // SYS_read
        svc 0
        ret

// write(int fd=r0, char *data=r1, int data_len=r2)
.globl write
write:
        mov x8, 0x40 // SYS_write
        svc 0
        ret

.globl ioctl
ioctl:
        mov x8, 29 // SYS_ioctl
        svc 0
        ret

.globl exit
exit:
        mov x8, 94 // SYS_exit_group
        svc 0
        ret

