#include <sys.h>
#include <random.h>

static int itoa(int64_t i, char *buffer) {
  int digits = 0;
  int64_t n;
  char *p;
  for (n = i; n; n /= 10) digits += 1;
  if (i < 0) digits ++;
  p = buffer + digits;
  *p = '\0';
  p--;

  for (n = i; n; n /= 10) {
    *p = '0' + (char)(n%10);
    p--;
  }
  if (i < 0) *p = '-';
  return digits;
}

int main() {
  char buffer[48];
  RandGen g = randinit();
  int i, size;
  int64_t n;
  int buckets[19];

  for(i = 0; i < 3000000; i++) {
    n = randnext(&g);
    buckets[n % 19] += 1;
  }
  for(i = 0; i < 19; i++) {
    size = itoa(buckets[i], buffer);
    buffer[size] = '\n';
    write(1, buffer, size+1);
  }
}
