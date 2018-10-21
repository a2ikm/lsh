.PHONY: all
all: lsh

builin.o: builtin.c
	clang -c builtin.c

main.o: main.c
	clang -c main.c

parser.o: parser.c
	clang -c parser.c

util.o: util.c
	clang -c util.c

lsh: builin.o main.o parser.o util.o
	clang -o lsh builtin.o main.o parser.o util.o

.PHONY: clean
clean:
	rm -rf lsh *.o
