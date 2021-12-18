#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>

#define print(x)                                                               \
  _Generic((x), int16_t                                                        \
           : printint, int32_t                                                 \
           : printint, int64_t                                                 \
           : printint, uint16_t                                                \
           : printuint, uint32_t                                               \
           : printuint, uint64_t                                               \
           : printuint, char*: printstr)(x)

void printint(int64_t n);
void printuint(uint64_t n);
void printstr(const char *s);

#endif
