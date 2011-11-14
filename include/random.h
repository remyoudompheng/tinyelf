#ifndef RANDOM_H
#define RANDOM_H

#include <types.h>

typedef struct  {
  int64 seed;
} RandGen;

RandGen randinit();
int64 randnext(RandGen *g);

#endif
