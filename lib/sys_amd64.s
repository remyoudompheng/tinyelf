.text
.globl write

// write(int fd, char *data, int data_len)
write:
        // fd in %edi, data in %rsi, data_len in %edx
        movl $1, %eax
        syscall
        ret

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


