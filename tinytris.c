#include <random.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys.h>
#include <termios.h>

#define FRAME_DURATION_USECS 200000
#define WIDTH 24

// contains ' ' or '#'
char board[10 * 20];
char screen[WIDTH * 21];

struct state {
  uint16_t score;
  int x, y;
  uint32_t shape, angle;
  uint16_t shpbits;
  RandGen g;

  char lastkey;
} state;

uint16_t getshape(uint32_t idx, uint32_t angle) {
  int shift1 = 16 * (angle & 1);
  int shift2 = 12 * (angle & 3);

  static const uint32_t shapes_sym[3] = {
      0x444400F0ul,
      //  ## #
      // ##  ##
      //      #
      0x02310036ul,
      // ##    #
      //  ##  ##
      //      #
      0x01320063ul,
  };

  static const uint64_t shapes_asym[3] = {
      // 270 262 072 232
      // ###  #   #   #
      //  #   ## ### ##
      //      #       #
      0x270262072232ull,
      // 170 622 074 223
      // ###  ##   #  #
      // #    #  ###  #
      //      #      ##
      0x170622074223ull,
      // 470 226 071 322
      0x470226071322ull,
  };

  switch (idx) {
  case 1:
  case 2:
  case 3:
    return (shapes_sym[idx - 1] >> shift1) & 0xffff;
  case 4:
    return 0x0660;
  case 5:
  case 6:
  case 7:
    return (shapes_asym[idx - 5] >> shift2) & 0xfff;
  default:
    exit(43); // impossible
  }
}

static bool fits(int px, int py) {
  for (int bit = 0; bit < 16; bit++) {
    int sx = px + bit % 4;
    int sy = py + bit / 4;
    if (((state.shpbits >> bit) & 1) == 0)
      continue;
    if (sx < 0 || sx >= 10)
      return false;
    if (sy < 0 || sy >= 20)
      return false;
    if (board[10 * sy + sx] != ' ')
      return false;
  }
  return true;
}

static inline void copy8(char *dst, const char *src) {
  *(uint64_t *)(dst) = *(uint64_t *)(src);
}

static inline void copy4(char *dst, const char *src) {
  *(uint32_t *)(dst) = *(uint32_t *)(src);
}

static inline void copy2(char *dst, const char *src) {
  *(uint16_t *)(dst) = *(uint16_t *)(src);
}

static void init_board() {
  for (int i = 0; i < 10 * 20; i++)
    board[i] = ' ';
}

// Find complete lines and pop them.
static void poplines(struct state *st) {
  for (int i = 0; i < 20; i++) {
    bool win = true;
    for (int j = 0; j < 10; j++) {
      if (board[10 * i + j] != '#')
        win = false;
    }
    if (win) {
      st->score++;
      // slide down
      for (int k = i; k > 0; k--) {
        copy8(&board[10 * k], &board[10 * (k - 1)]);
        copy2(&board[10 * k + 8], &board[10 * (k - 1) + 8]);
      }
      // top line
      for (int j = 0; j < 10; j++)
        board[j] = ' ';
    }
  }
}

static void init_screen() {
  for (int i = 0; i <= 20; i++) {
    for (int j = 0; j < WIDTH; j++) {
      char c = ' ';
      if (j == 10)
        c = '|';
      if (i == 20 && j <= 10)
        c = '-';
      if (j == WIDTH - 1)
        c = '\n';
      screen[WIDTH * i + j] = c;
    }
  }
  // help
  const char s0[8] = "  LINES ";
  copy8(&screen[WIDTH * 7 + 13], s0);
  const char s2[8] = "2 down  ";
  copy8(&screen[WIDTH * 11 + 13], s2);
  const char s4[4] = "4 <-";
  copy4(&screen[WIDTH * 12 + 13], s4);
  const char s5[8] = "5 rotate";
  copy8(&screen[WIDTH * 13 + 13], s5);
  const char s6[4] = "6 ->";
  copy4(&screen[WIDTH * 14 + 13], s6);
  const char sq[8] = "q quit  ";
  copy8(&screen[WIDTH * 15 + 13], sq);
}

void update_screen(struct state *st) {
  for (int i = 0; i < 20; i++) {
    // copy 10 bytes
    *(uint64_t *)(&screen[WIDTH * i]) = *(uint64_t *)(&board[10 * i]);
    *(uint16_t *)(&screen[WIDTH * i + 8]) = *(uint16_t *)(&board[10 * i + 8]);
  }
  // draw shape
  for (int bit = 0; bit < 16; bit++) {
    int sx = st->x + bit % 4;
    int sy = st->y + bit / 4;
    if ((st->shpbits >> bit) & 1)
      screen[WIDTH * sy + sx] = '@';
  }
  // show score on line 8:
  uint16_t score = st->score;
  if (score >= 1000)
    score = 999;
  char score_str[4] = {
      ' ',
      score >= 100 ? '0' + (score / 100) : ' ',
      score >= 10 ? '0' + ((score / 10) % 10) : ' ',
      '0' + (score % 10),
  };
  copy4(&screen[WIDTH * 8 + 14], score_str);
}

static void rewind() {
  const char esc[6] = "\r\e[21A";
  write(1, esc, 6);
}

static void show_screen() { write(1, screen, WIDTH * 21); }

static void newshape(struct state *st) {
  while (1) {
    uint64_t rnd = (uint64_t)randnext(&st->g);
    uint32_t s = (rnd >> 16) % 8;
    uint32_t s2 = (rnd >> 28) % 4;
    if (s > 0) {
      st->x = 3;
      st->y = 0;
      st->shape = s;
      st->angle = s2;
      st->shpbits = getshape(s, s2);
      return;
    }
  }
}

void next_frame(struct state *st) {
  // Wait for next frame or next key.
  struct UTime dt = {0, FRAME_DURATION_USECS};
  // Bitmask for stdin
  uint64_t readmask = 1;
  select(1, &readmask, NULL, NULL, &dt);
  if (readmask & 1) {
    char key;
    read(0, &key, 1);
    st->lastkey = key;
  } else {
    st->lastkey = ' ';
  }
  // handle controls
  const int x = st->x;
  const int y = st->y;
  switch (st->lastkey) {
  case '4':
    if (fits(x - 1, y))
      st->x--;
    return;
  case '5':
    st->angle++;
    st->shpbits = getshape(st->shape, st->angle);
    if (!fits(x, y)) {
      st->angle--;
      st->shpbits = getshape(st->shape, st->angle);
    }
  case '6':
    if (fits(x + 1, y))
      st->x++;
    return;
  case 'q':
    exit(0);
  }
  // move shape down
  if (fits(x, y + 1))
    st->y++;
  else {
    // freeze shape
    if (fits(x, y)) {
      for (int bit = 0; bit < 16; bit++) {
        int sx = st->x + bit % 4;
        int sy = st->y + bit / 4;
        if (((st->shpbits >> bit) & 1) == 0)
          continue;
        board[10 * sy + sx] = '#';
      }
    } else {
      // impossible
      exit(42);
    }
    poplines(st);
    newshape(st);

    if (!fits(st->x, st->y)) {
      write(1, "GAME OVER\n", 10);
      exit(1);
    }
  }
}

static void setup_tty() {
  // Deactivate echo and buffering.
  struct termios st;
  ioctl(0, TCGETS, &st);
  st.c_lflag &= ~(uint32_t)(ICANON | ECHO);
  ioctl(0, TCSETSF, &st);
}

int main() {
  state.lastkey = ' ';
  state.score = 0;
  setup_tty();
  init_board();
  init_screen();
  show_screen();
  newshape(&state);
  while (1) {
    update_screen(&state);
    rewind();
    show_screen();
    next_frame(&state);
  }
  return 0;
}
