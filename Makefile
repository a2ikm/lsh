.PHONY: all
all: lsh

lsh: main.c
	clang -o lsh main.c

.PHONY: clean
clean:
	rm -rf lsh
