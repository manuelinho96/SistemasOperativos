CC = gcc
GCC = gcc -c
CCFLAGS = -g -Wall -std=gnu99

arbol: main.c navdirectory.o palindromo.o
	$(CC) $(CCFLAGS) main.c navdirectory.o palindromos.o -o $@ -lm

navdirectory.o:
	$(GCC) navdirectory.c

palindromo.o:
	$(GCC) palindromos.c

.PHONY: clean

clean:
	rm -rf *.o arbol caminos.txt