# Fro linux i386
CPPFLAGS = -DARCH=32 -Iinclude

OBJS = lib/skel.o lib/sys.o main.o

%.o: %.s
	$(CC) $(CPPFLAGS) -o $@ -c $<

main: $(OBJS)
	ld -s -o main $(OBJS)

clean:
	rm -f main *.o lib/*.o
