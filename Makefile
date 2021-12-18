ARCH = $(shell uname -m)
# no-builtin: do not generate memcpy() calls
# no-stack-protector: do not attempt to load SSP canary from TLS
# no-unwind-tables: avoid eh_frame sections on AArch64
# no-asynchronous-unwind-tables: avoid eh_frame sections
CFLAGS = -Os -march=native -std=c11 -pipe -Wall -Wconversion \
	 -fno-builtin \
	 -fno-jump-tables \
	 -fno-stack-protector \
	 -ffunction-sections \
	 -fno-unwind-tables \
	 -fno-asynchronous-unwind-tables
CPPFLAGS = -Iinclude
LD ?= ld.gold
LDFLAGS = -s -N -O3 --gc-sections

ifdef DEBUG
CFLAGS += -O0 -g -fasynchronous-unwind-tables
LDFLAGS =
endif

ifeq ($(ARCH), i686)
    CPPFLAGS += -DARCH_386
else ifeq ($(ARCH), aarch64)
    CPPFLAGS += -DARCH_aarch64
else
    CFLAGS += -m64
    LDFLAGS += -melf_x86_64
    CPPFLAGS += -DARCH_amd64
    ARCH = amd64
endif

LIB_OBJS = lib/print.o lib/time.o lib/int64.o lib/random.o lib/stub.o
LIB_OBJS += lib/$(ARCH)/skel.o lib/$(ARCH)/sys.o lib/$(ARCH)/sys_time.o

all: main.bin mandelbrot.bin random.bin randomline.bin tinytris.bin

%.bin: %.o stdlib.a
	$(LD) $(LDFLAGS) -o $@ $< stdlib.a

%.o: %.s
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

stdlib.a: $(LIB_OBJS)
	ar cru stdlib.a $(LIB_OBJS)

format:
	clang-format -i *.c include/*.h lib/*.c

clean:
	rm -f *.bin *.o lib/*.o lib/*/*.o stdlib.a
