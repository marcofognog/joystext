build:
	flex src/lexer.l
	bison -d src/parser.y
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ src/main.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -lfl -o bin/joystext

buildspec:
	cp src/* spec/src
	cp spec/replace/* spec/src
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ spec/src/main.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o spec/bin/ex1

spec: buildspec
	rspec

clean:
	rm -f bin/joystext
	rm -f spec/bin/ex1

inspect:
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ src/inspect.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -o bin/inspect

unitspec:
	gcc -std=c99 -Wall -g -I/usr/include/SDL2/ src/unitspec.c -L/usr/local/lib/ -lSDL -lXtst -lX11 -lfl -o bin/unitspec
