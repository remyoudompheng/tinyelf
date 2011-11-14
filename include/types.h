#ifndef TYPES_H
#define TYPES_H

#define NULL ((void*)0)

typedef long long int int64;

struct UTime {
  long int secs;
  long int usecs;
};

struct NTime {
  long int secs;
  long int nsecs;
};

struct Timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

#endif
