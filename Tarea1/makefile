CC = gcc
GCC = gcc -c
CCFLAGS = -g -Wall -std=gnu99

mercado: main.c cola.o lista.o configuracion.o simulacion.o pila.o
	$(CC) $(CCFLAGS) main.c cola.o ListaEnlazada.o stack.o configuracion.o simulacion.o -o $@ -lm

cola.o: cola.c producto.h
	$(GCC) cola.c

lista.o: ListaEnlazada.c producto.h
	$(GCC) ListaEnlazada.c

configuracion.o: configuracion.c simulacion.h globals.h
	$(GCC) configuracion.c

simulacion.o: simulacion.c ListaEnlazada.h globals.h
	$(GCC) simulacion.c

pila.o: stack.c producto.h
	$(GCC) stack.c

.PHONY: clean

clean:
	rm -rf *.o mercado
