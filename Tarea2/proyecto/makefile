# Este makefile crea un ejecutable Arbol
# Las dependencias del ejecutable son navdirectory y palindromo
# Para limpiar los archivos creados se implemento un clean.

CC = gcc
GCC = gcc -c
CCFLAGS = -g -Wall -std=gnu99

arbol: main.c navdirectory.o palindromo.o
	$(CC) $(CCFLAGS) main.c navdirectory.o palindromos.o -o $@ -lm

navdirectory.o: navdirectory.h
	$(GCC) navdirectory.c

palindromo.o: palindromos.h
	$(GCC) palindromos.c

.PHONY: clean

clean:
	rm -rf *.o arbol caminos.txt