/* IMPLEMENTACION DE LA ESTRUCTURA DE DATOS COLA

Estudiantes:
- Ian Goldberg		# 14-10406
- Manuel Rodriguez	# 13-11223
- David Segura		# 13-11341
*/

#include <stdlib.h>
#include <stdio.h>
#define __PRODUCTOS__
#include "producto.h"

/************************ NODOCOLA ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de un nodo que contendra dos
estructuras para conformar una lista de productos */

struct nodocola {
    struct Producto *Dato;
    struct nodocola *siguiente;
};

/************************ COLA ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de un estructura que contendra dos
nodos para simular una cola */

typedef struct Cola{
    struct nodocola *nraiz;
    struct nodocola *nfinal;
}ColaCarrito;

// Funcion para iniciar la cola.
void iniciarcola(ColaCarrito * cola);

// Determinar si la cola esta vacia.
int colavacia(ColaCarrito *cola);

// Insertar un nodo en la cola.
void insertarnodocola(struct Producto *producto, ColaCarrito *cola);

// Imprimir la cola.
void imprimircola(ColaCarrito *cola);

// Liberar el contenido de una cola.
void liberarcola(ColaCarrito *cola);

//Extraer un nodo de la cola.
struct Producto *extraernodocola(ColaCarrito *cola);