CFLAGS = -g -std=c99 -Wall -Wextra -pedantic -I. -I/usr/local/include  
LDFLAGS = -g -L/usr/local/lib 

build: clean main

main: main.o data.o node.o hash.o
	gcc $^ -lm -o $@ $(LDFLAGS)

main.o: main.c
	gcc $(CFLAGS) -c $< -o $@

data.o: src/data.c
	gcc $(CFLAGS) -c $< -o $@

node.o: src/node.c
	gcc $(CFLAGS) -c $< -o $@

hash.o: src/hash.c
	gcc $(CFLAGS) -c $< -o $@

run: main
	./main

debug: clean main
	gdb --tui ./main

clean:
	echo `clear`
	rm -f main *.o 

all: clean build run
