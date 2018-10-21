.PHONY: all
all: lsh

builin.o: builtin.c
	clang -c builtin.c

main.o: main.c
	clang -c main.c

lsh: builin.o main.o
	clang -o lsh main.o builtin.o

.PHONY: clean
clean:
	rm -rf lsh *.o
