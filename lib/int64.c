#if ARCH == i386

#include <stddef.h>
#include <stdint.h>

typedef size_t uint;

static void quotrem64(a, b, q, r)
  uint64_t a, b;
  uint64_t *q, *r;
{
  double qfloat;

  // Special case
  if (a < b) { *q = 0; if (r != NULL) *r = a; }

  // Use float for approximation
  qfloat = (double)a / (double)b;
  if (b >> 16) {
    // Quotient has less than 48 bits
    *q = (uint64_t)qfloat;
    if (r != NULL) *r = a - b * (*q);
  } else {
    uint64_t qapprox, rem;
    qapprox = (uint64_t)qfloat;
    rem = a - b * qapprox;
    *q = qapprox + (uint64_t)((uint)rem / (uint)b);
    if (r != NULL) *r = (uint)rem % (uint)b;
  }
}

#define ONE_FOURTH      (1 << 30)
#define ONE_HALF        (ONE_FOURTH * 2.0)
#define ONE             (ONE_FOURTH * 4.0)

uint64_t __fixunsdfdi(double x) {
  double upper = x / ONE;
  uint64_t result = (uint)upper;
  result <<= 32;
  while(result > x) result -= (1ULL<<32);
  x -= (double)result;
  result += (uint)x;
  return result;
}

uint64_t __divdi3(uint64_t a, uint64_t b) {
  uint64_t q;
  quotrem64(a, b, &q, NULL);
  return q;
}

uint64_t __moddi3(uint64_t a, uint64_t b) {
  uint64_t q, r;
  quotrem64(a, b, &q, &r);
  return r;
}

#endif
