main.o: main.c cola.o lista.o configuracion.o simulacion.o pila.o
	gcc -g main.c cola.o ListaEnlazada.o configuracion.o simulacion.o stack.o -o $@	

cola.o: cola.c producto.h
	gcc -c cola.c

lista.o: ListaEnlazada.c producto.h
	gcc -c ListaEnlazada.c

configuracion.o: configuracion.c simulacion.h
	gcc -c configuracion.c

simulacion.o: simulacion.c ListaEnlazada.h
	gcc -c simulacion.c

pila.o: stack.c producto.h
	gcc -c stack.c