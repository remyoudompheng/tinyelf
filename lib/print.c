#include <stdint.h>
#include <sys.h>

void printuint(uint64_t n) {
  char digits[20];
  int x = 19;
  uint64_t hi = 0;
  const uint64_t N_1E9 = 1000000000;
  while (n) {
    if (n >= N_1E9) {
      hi = n / N_1E9;
      uint32_t lo = (uint32_t)(n % N_1E9);
      for (int i = 0; i < 9; i++) {
        uint32_t digit = lo % 10;
        lo = lo / 10;
        digits[x] = '0' + (char)digit;
        x--;
      }
      n = hi;
    } else {
      uint32_t lo = (uint32_t)n;
      uint32_t digit = lo % 10;
      lo = lo / 10;
      digits[x] = '0' + (char)digit;
      x--;
      n = lo;
    }
  }
  if (x == 19) {
    digits[x] = '0';
    x--;
  }
  write(1, &digits[x + 1], 19 - x);
}

void printint(int64_t n) {
  if (n < 0) {
    char minus = '-';
    write(1, &minus, 1);
    printuint((uint64_t)(-n));
  } else {
    printuint((uint64_t)(n));
  }
}

void printstr(const char *s) {
  char *p = s;
  int l = 0;
  while (*p) {
    l++;
    p++;
  }
  write(1, s, l);
}
