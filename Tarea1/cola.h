#include <stdlib.h>
#include <stdio.h>
#define __PRODUCTOS__
#include "producto.h"

// Estructura de los nodos

struct nodocola {
    struct Producto *Dato;
    struct nodocola *siguiente;
};

// Estructura de cola

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