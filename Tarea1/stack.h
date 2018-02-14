#include <stdio.h>
#include <stdlib.h>
#ifndef __PRODUCTOS__
#define __PRODUCTOS__
#include "producto.h"
#endif

/************************ LISTELEMENT ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de un nodo que contendra dos
estructuras para simular una lista simple */
typedef struct StackElement{
	struct Producto *item; 
	struct StackElement *next;
}Element;

/************************ LISTELEMENT ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de un nodo que contendra una
estructura con el primer elemento de la lista y un entero
que representara la cantidad de elementos en la lista, simulando
de esta manera una pila */
typedef struct ListLocation{
	Element *head;
	int size;
}Stack;

// Inicializar una pila.
void initialization(Stack *s);

// Agregar un elemento a la pila.
int push(Stack *s, struct Producto *itm);

// Eliminar un producto de la pila.
struct Producto *pop(Stack *s);

// Imprimir pila.
void show(Stack *s);

// Calcular area de una pila.

int AreaPila(Stack *s);