#if ARCH == i386

#define NULL ((void*)0)

typedef unsigned int uint;
typedef unsigned long long int uint64;

static void quotrem64(a, b, q, r)
  uint64 a, b;
  uint64 *q, *r;
{
  double qfloat;

  // Special case
  if (a < b) { *q = 0; if (r != NULL) *r = a; }

  // Use float for approximation
  qfloat = (double)a / (double)b;
  if (b >> 16) {
    // Quotient has less than 48 bits
    *q = (uint64)qfloat;
    if (r != NULL) *r = a - b * (*q);
  } else {
    uint64 qapprox, rem;
    qapprox = (uint64)qfloat;
    rem = a - b * qapprox;
    *q = qapprox + (uint64)((uint)rem / (uint)b);
    if (r != NULL) *r = (uint)rem % (uint)b;
  }
}

#define ONE_FOURTH      (1 << 30)
#define ONE_HALF        (ONE_FOURTH * 2.0)
#define ONE             (ONE_FOURTH * 4.0)

uint64 __fixunsdfdi(double x) {
  double upper = (x - ONE_HALF) / ONE;
  uint64 result = (uint)upper;
  result <<= 32;
  x -= (double)result;
  result += (uint)x;
  return result;
}

uint64 __divdi3(uint64 a, uint64 b) {
  uint64 q;
  quotrem64(a, b, &q, NULL);
  return q;
}

uint64 __moddi3(uint64 a, uint64 b) {
  uint64 q, r;
  quotrem64(a, b, &q, &r);
  return r;
}

#endif
