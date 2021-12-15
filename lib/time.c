#include <sys.h>

void usleep(unsigned long usecs) {
  struct NTime t;
  t.secs = usecs / 1000000;
  t.nsecs = 1000 * (usecs % 1000000);
  nanosleep(&t, NULL);
}

int64_t utime() {
  struct UTime t;
  gettimeofday(&t, NULL);
  return t.secs * 1000000 + t.usecs;
}
