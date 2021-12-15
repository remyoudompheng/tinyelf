#include "sys.h"

#define ROWS 25
#define COLS 80
#define ASPECT 1.6
#define VERBATIM(s) #s
#define AS_STRING(s) VERBATIM(s)

const char *header = "\r\e[" AS_STRING(ROWS) "A";

static int test(c1, c2) double c1, c2; {
  double x, y;
  x = y = 0;
  for(int n = 0; n < 1000; n++) {
    double newx = x*x - y*y + c1;
    double newy = 2*x*y + c2;
    x = newx; y = newy;
    if ((x*x + y*y) > 10.0) {
      return n/124;
    }
  }
  return 9;
}

// double refx = 0.3245046418497685;
// double refy = 0.04855101129280834;

//double refx = 0.3215000630401344;
//double refy = 0.04855009999999;

//double refx = 0.32158;
//double refy = 0.048;

double refx = 0.32151002;
double refy = 0.04800001;

char buffer[32768];

int main() {
  int pos = 0;
  double scale = 2;
  double x, y;
  for(int i = 0; i < 610; i++) {
    y = refy + scale;
    for(int i = 0; i < ROWS; i++) {
      x= refx - scale * ASPECT;
      y -= 2 * scale / (double)(ROWS);
      for(int j = 0; j < COLS; j++) {
        x += 2 * scale / (double)(COLS) * ASPECT;
        int r = test(x,y);
        buffer[pos++] = '\e';
        buffer[pos++] = '[';
        buffer[pos++] = '4';
        buffer[pos++] = r+'0';
        buffer[pos++] = 'm';
        buffer[pos++] = ' ';
      }
      buffer[pos++] = '\e';
      buffer[pos++] = '[';
      buffer[pos++] = '0';
      buffer[pos++] = 'm';
      buffer[pos++] = '\n';
    }
    write(1, buffer, pos);
    usleep(30000);
    scale *= 0.95;
    // Rewind cursor
    pos = 0;
    for (const char *p = header; *p; p++) buffer[pos++] = *p;
  }
  return 0;
}

