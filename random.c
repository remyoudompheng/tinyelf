#include <print.h>
#include <random.h>
#include <sys.h>

int main() {
  RandGen g = randinit();
  int i;
  int64_t n;
  int buckets[19];

  for (i = 0; i < 3000000; i++) {
    n = randnext(&g);
    buckets[n % 19] += 1;
  }
  for (i = 0; i < 19; i++) {
    print(buckets[i]);
    print("\n");
  }
}
