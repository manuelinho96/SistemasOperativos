CC = gcc
GCC = gcc -c
CCFLAGS = -g -Wall -std=gnu99

arbol: main.c navdirectory.o
	$(CC) $(CCFLAGS) main.c navdirectory.o -o $@ -lm

navdirectory.o:
	$(GCC) navdirectory.c

.PHONY: clean

clean:
	rm -rf *.o mercado