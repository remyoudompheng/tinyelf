// pselect6(int n, void *read_fds, void *write_fds, void *err_fds, void *tv, void *sigmask)
.section .text.pselect6
.globl pselect6
pselect6:
        mov x8, 0x48 // SYS_pselect6
        svc 0
        ret

// nanosleep(timespec *t, timespec *rem)
.section .text.nanosleep
.globl nanosleep
nanosleep:
        mov x8, 0x65 // SYS_nanosleep
        svc 0
        ret

// gettimeofday(timeval *t, timezone *tz)
.section .text.gettimeofday
.globl gettimeofday
gettimeofday:
        mov x8, 0xa9
        svc 0
        ret

