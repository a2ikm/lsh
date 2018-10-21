.PHONY: all
all: lsh

builin.o: builtin.c
	clang -c builtin.c

main.o: main.c
	clang -c main.c

parser.o: parser.c
	clang -c parser.c

lsh: builin.o main.o parser.o
	clang -o lsh builtin.o main.o parser.o

.PHONY: clean
clean:
	rm -rf lsh *.o
