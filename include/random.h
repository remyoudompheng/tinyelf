#ifndef RANDOM_H
#define RANDOM_H

#include <sys.h>

typedef struct  {
  int64 seed;
} RandGen;

RandGen randinit();
int64 randnext(RandGen *g);

#endif
