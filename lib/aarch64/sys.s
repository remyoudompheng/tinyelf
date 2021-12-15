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

// select(int n, void *read_fds, void *write_fds, void *err_fds, void *tv)
.globl select
select:
        mov x8, 0x48 // SYS_pselect6
        svc 0
        ret

// nanosleep(timespec *t, timespec *rem)
.globl nanosleep
nanosleep:
        mov x8, 0x65 // SYS_nanosleep
        svc 0
        ret

// gettimeofday(timeval *t, timezone *tz)
.globl gettimeofday
gettimeofday:
        mov x8, 0xa9
        svc 0
        ret

