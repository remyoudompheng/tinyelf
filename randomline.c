#include <memory.h>
#include <random.h>
#include <sys.h>

#define BUFSIZE 4096

static void copybytes(char *dest, const char *src, int length) {
  register const char *p;
  const char *end = src + length;
  for (p = src; p < end; p++)
    *dest++ = *p;
}

// Copy a line including the terminating \n and returns the length.
static int readline(char *dest, int destsize) {
  static char buffer[BUFSIZE];
  static int pos;
  if (pos < BUFSIZE / 2) {
    int n_read = read(0, buffer + pos, BUFSIZE - pos);
    if ((n_read == 0) && (pos == 0)) {
      write(2, "End of file.\n", 13);
      return -1;
    }
    pos += n_read;
  }

  for (const char *p = buffer; p < buffer + pos; p++) {
    if (*p == '\n') {
      p++;
      int linelength = p - buffer;
      copybytes(dest, buffer, linelength);
      copybytes(buffer, p, BUFSIZE - linelength);
      pos -= linelength;
      return linelength;
    }
  }
  write(2, "Buffer capacity exceeded\n", 25);
  return -1;
}

int main() {
  char selected[4096];
  char buffer[4096];
  int lineno = 0;
  int selsize = 0;
  RandGen g = randinit();
  for (;;) {
    int len = readline(buffer, 4096);
    if (len <= 0)
      break;
    lineno++;
    int64_t rnd = randnext(&g);
    if (rnd % lineno == 0) {
      copybytes(selected, buffer, len);
      selsize = len;
    }
  }
  write(1, selected, selsize);
  return 0;
}
