#ifndef SYS_H
#define SYS_H

struct UTime {
  long secs;
  long usecs;
};

int write(int fd, const char *buffer, int size);
int select(int n, void *r, void *w, void *e, struct UTime *tv);
void usleep(unsigned long usecs);

#endif

