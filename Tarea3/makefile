CC = gcc
GCC = gcc -c
CCFLAGS = -g -W -std=gnu99

buscador_indexador: main.h funciones.o tablahash.o funciones.h tablahash.h
	$(CC) $(CCFLAGS) main.c funciones.o tablahash.o -l pthread -o $@ -lm

funciones.o: funciones.c funciones.h
	$(GCC) funciones.c

tablahash.o: tablahash.c tablahash.h
	$(GCC) tablahash.c

.PHONY: clean

clean:
	rm -rf *.o buscador_indexador