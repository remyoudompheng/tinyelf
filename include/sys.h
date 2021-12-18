#ifndef SYS_H
#define SYS_H

#include <types.h>

int read(int fd, const char *buffer, int size);
int write(int fd, const char *buffer, int size);
int ioctl(int fd, int cmd, void *args);
void exit(int code);

int select(int n, void *r, void *w, void *e, struct UTime *tv);

void nanosleep(struct NTime *t, struct NTime *rem);
void usleep(unsigned long usecs);

int gettimeofday(struct UTime *t, struct Timezone *tz);
int64_t utime();

// ioctl constants
#define TCGETS 0x5401
#define TCSETSF 0x5404

#endif
