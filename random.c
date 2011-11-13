#include <sys.h>

static int64 seed;

static void randinit() {
  seed = utime();
}

static int64 randnext() {
  seed = 0x5DEECE66D * seed + 0xB;
  seed &= 0xffffffffffff;
  return seed;
}

static int itoa(int64 i, char *buffer) {
  int digits = 0;
  int64 n;
  char *p;
  for (n = i; n; n /= 10) digits += 1;
  if (i < 0) digits ++;
  p = buffer + digits;
  *p = '\0';

  for (n = i; n; n /= 10) {
    *p = '0' + (char)(n%10);
    p--;
  }
  if (i < 0) *p = '-';
  return digits;
}

int main() {
  char buffer[48];
  int i, size;
  int64 n;

  randinit();
  for(i = 0; i < 30; i++) {
    n = randnext();
    size = itoa(n, buffer);
    buffer[size] = '\n';
    write(1, buffer, size+1);
  }
}
