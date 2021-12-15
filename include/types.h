#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <stdint.h>

struct UTime {
  size_t secs;
  size_t usecs;
};

struct NTime {
  size_t secs;
  size_t nsecs;
};

struct Timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

#endif
