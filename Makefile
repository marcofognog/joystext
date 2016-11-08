CFLAGS=-Wall -g `pkg-config --cflags --libs sdl2` -I/usr/include/SDL2/

all: ex1

clean:
	rm -f ex1
