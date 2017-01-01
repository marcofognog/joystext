build:
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ main.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o bin/ex1

clean:
	rm -f bin/ex1
