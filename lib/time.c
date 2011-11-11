#include <sys.h>

void usleep(unsigned long usecs) {
  struct UTime t;
  t.secs = usecs / 1000000;
  t.usecs = usecs % 1000000;
  select(0, 0, 0, 0, &t);
}
