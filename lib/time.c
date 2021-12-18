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

#if ARCH_aarch64
// emulate select with pselect6

int pselect6(int nfds, void *r, void *w, void *e, struct NTime *t, void *p);

int select(int nfds, void *r, void *w, void *e, struct UTime *t) {
  struct NTime nt = {t->secs, 1000 * t->usecs};
  int ret = pselect6(nfds, r, w, e, &nt, NULL);
  return ret;
}
#endif
