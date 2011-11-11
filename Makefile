ARCH = i386
CFLAGS = -Os -std=c99 -pipe -Wall
CPPFLAGS = -Iinclude
LDFLAGS = -s

ifeq ($(ARCH), i386)
    CPPFLAGS += -DARCH=i386
    LIB_OBJS = lib/skel.o lib/sys_i386.o
else
    CPPFLAGS += -DARCH=amd64
    LIB_OBJS = lib/skel.o lib/sys_amd64.o
endif

all: main mandelbrot

main: main.o stdlib.a
	ld $(LDFLAGS) -o main main.o stdlib.a

mandelbrot: mandelbrot.o stdlib.a
	ld $(LDFLAGS) -o mandelbrot mandelbrot.o stdlib.a

%.o: %.s
	$(CC) $(CPPFLAGS) -o $@ -c $<

stdlib.a: $(LIB_OBJS)
	ar cru stdlib.a $(LIB_OBJS)

clean:
	rm -f main *.o lib/*.o stdlib.a
