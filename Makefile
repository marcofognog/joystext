build:
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ src/main.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o bin/ex1

buildspec:
	cp src/* spec/src
	cp spec/replace/* spec/src
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ spec/src/main.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o spec/bin/ex1

spec: buildspec
	rspec

clean:
	rm -f bin/ex1
	rm -f spec/bin/ex1

inspect:
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ src/inspect.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o bin/inspect
