ARCH = $(shell uname -m)
# no-builtin: do not generate memcpy() calls
# no-stack-protector: do not attempt to load SSP canary from TLS
CFLAGS = -O2 -march=native -std=c99 -pipe -Wall -Wconversion -fno-builtin -fno-stack-protector
CPPFLAGS = -Iinclude
LDFLAGS = -s

ifdef DEBUG
CFLAGS += -O0 -g
LDFLAGS =
endif

LIB_OBJS = lib/time.o lib/int64.o lib/random.o lib/stub.o

ifeq ($(ARCH), i686)
    CPPFLAGS += -DARCH=i386
    LIB_OBJS += lib/skel.o lib/i386/sys.o
else
    CFLAGS += -m64
    LDFLAGS += -melf_x86_64
    CPPFLAGS += -DARCH=amd64
    LIB_OBJS += lib/skel.o lib/amd64/sys.o
endif

all: main.bin mandelbrot.bin random.bin randomline.bin

%.bin: %.o stdlib.a
	$(LD) $(LDFLAGS) -o $@ $< stdlib.a

%.o: %.s
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

stdlib.a: $(LIB_OBJS)
	ar cru stdlib.a $(LIB_OBJS)

clean:
	rm -f *.bin *.o lib/*.o lib/*/sys.o stdlib.a
