#include "sys.h"

int test(c1, c2) double c1, c2; {
  double x, y;
  x = y = 0;
  for(int n = 0; n < 16; n++) {
    double newx = x*x - y*y + c1;
    double newy = 2*x*y + c2;
    x = newx; y = newy;
    if ((x*x + y*y) > 10.0) {
      return 0;
    }
  }
  return 1;
}

int main() {
  char buffer[2048];
  int pos = 0;
  for(int i = 0; i < 25; i++) {
    for(int j = 0; j < 80; j++) {
      double x = (j - 40.0) / 20;
      double y = (i - 12.0) / 10;
      buffer[pos++] = test(x,y) ? '*' : ' ';
    }
    buffer[pos++] = '\n';
  }
  write(1, buffer, pos);
  return 0;
}
