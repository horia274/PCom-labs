CC=gcc

.PHONY: build clean

build: cat tac

cat: cat.c utils.h
	$(CC) $< -o $@

tac: tac.c utils.h
	$(CC) $< -o $@

clean:
	rm -rf cat tac
