.text

// select
//    int n           %edi
//    void *read_fds  %rsi
//    void *write_fds %rdx
//    void *err_fds   %rcx
//    void *tv        %r8
.globl select
select:
        movl $23, %eax
        movq %rcx, %r10
        syscall
        ret

// nanosleep(timespec *t, timespec *rem)
.globl nanosleep
nanosleep:
        movl $35, %eax
        syscall
        ret

// gettimeofday(timeval *t, timezone *tz)
.globl gettimeofday
gettimeofday:
        movl $96, %eax
        syscall
        ret

