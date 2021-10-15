CC=clang
CFLAGS=-I./include
to_ppm: to_ppm.c
	$(CC) $(CFLAGS) -o $@ $< -ljpeg

clean:
	rm to_ppm
