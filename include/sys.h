#ifndef SYS_H
#define SYS_H

#define NULL ((void*)0)

struct UTime {
  long int secs;
  long int usecs;
};

struct NTime {
  long int secs;
  long int nsecs;
};

int write(int fd, const char *buffer, int size);
int select(int n, void *r, void *w, void *e, struct UTime *tv);
void nanosleep(struct NTime *t, struct NTime *rem);
void usleep(unsigned long usecs);

#endif

