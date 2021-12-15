#include <sys.h>
#include <random.h>

RandGen randinit();
int64_t randnext(RandGen *g);

RandGen randinit() {
  RandGen g;
  g.seed = utime();
  return g;
}

int64_t randnext(RandGen *g) {
  int64_t ret = g->seed;
  ret = 0x5DEECE66D * ret + 0xB;
  ret &= 0xffffffffffff;
  g->seed = ret;
  ret = ret ^ (ret >> 16) ^ (ret >> 32);
  return ret;
}

