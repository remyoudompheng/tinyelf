#ifndef RANDOM_H
#define RANDOM_H

#include <types.h>

typedef struct  {
  int64_t seed;
} RandGen;

RandGen randinit();
int64_t randnext(RandGen *g);

#endif
