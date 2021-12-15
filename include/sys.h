#ifndef SYS_H
#define SYS_H

#include <types.h>

int read(int fd, const char *buffer, int size);
int write(int fd, const char *buffer, int size);

int select(int n, void *r, void *w, void *e, struct UTime *tv);

void nanosleep(struct NTime *t, struct NTime *rem);
void usleep(unsigned long usecs);

int gettimeofday(struct UTime *t, struct Timezone *tz);
int64_t utime();

#endif

