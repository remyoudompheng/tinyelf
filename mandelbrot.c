#include "sys.h"

int test(c1, c2) double c1, c2; {
  double x, y;
  x = y = 0;
  for(int n = 0; n < 1000; n++) {
    double newx = x*x - y*y + c1;
    double newy = 2*x*y + c2;
    x = newx; y = newy;
    if ((x*x + y*y) > 10.0) {
      return 0;
    }
  }
  return 1;
}

double refx = .44;
double refy = .374;

int main() {
  char buffer[2048];
  int pos = 0;
  double scale = 2;
start:
  pos = 0;
  // Erase screen
  buffer[pos++] = '\e';
  buffer[pos++] = '[';
  buffer[pos++] = '2';
  buffer[pos++] = 'J';
  for(int i = 0; i < 30; i++) {
    for(int j = 0; j < 80; j++) {
      double x = refx + (j - 40.0) / 20.0 * scale;
      double y = refy + (i - 15.0) / 10.0 * scale;
      buffer[pos++] = test(x,y) ? '*' : ' ';
    }
    buffer[pos++] = '\n';
  }
  write(1, buffer, pos);
  usleep(100000);
  scale *= 0.98;
  goto start;
  return 0;
}
