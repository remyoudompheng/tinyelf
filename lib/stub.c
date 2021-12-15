#include <sys.h>

void __stack_chk_fail() {
  write(2, "stack overflow\n", 15);
}
