ARCH = $(shell arch)
CFLAGS = -O2 -march=native -std=c99 -pipe -Wall -Wconversion
CPPFLAGS = -Iinclude
LDFLAGS = -s

ifdef DEBUG
CFLAGS = -pipe -ggdb3 -Wall -std=c99
LDFLAGS = 
endif

LIB_OBJS = lib/time.o lib/int64.o

ifeq ($(ARCH), i686)
    CPPFLAGS += -DARCH=i386
    LIB_OBJS += lib/skel.o lib/sys_i386.o
else
    CPPFLAGS += -DARCH=amd64
    LIB_OBJS += lib/skel.o lib/sys_amd64.o
endif

all: main mandelbrot random

main: main.o stdlib.a
	$(LD) $(LDFLAGS) -o main main.o stdlib.a

mandelbrot: mandelbrot.o stdlib.a
	$(LD) $(LDFLAGS) -o mandelbrot mandelbrot.o stdlib.a

random: random.o stdlib.a
	$(LD) $(LDFLAGS) -o random random.o stdlib.a

%.o: %.s
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

stdlib.a: $(LIB_OBJS)
	ar cru stdlib.a $(LIB_OBJS)

clean:
	rm -f main mandelbrot *.o lib/*.o stdlib.a
