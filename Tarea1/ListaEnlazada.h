#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __PRODUCTOS__
#define __PRODUCTOS__
#include "producto.h"
#endif

// Estructura de nodo lista.
// Los nodos almacenan bolsas de productos o un producto.
// La lista se utiliza para almacenar productos de un carrito
// O para almacenar lista de bolsas.

struct NodoLista
{
    struct ListaEnlazada *Bolsa;
    struct Producto * Dato;
    struct NodoLista * next;
    int esBolsa;
};

// Definicion de la lista enlazada.

typedef struct ListaEnlazada
{
    struct NodoLista * head;
}ListaEnlazada;

// Iniciarlizar lista

void Inicialize(struct ListaEnlazada * Lista);

// Funcion para añadir una bolsa a una lista.

int anadirbolsa(struct ListaEnlazada * Lista, struct ListaEnlazada *Bolsa);

// Funcion para añadir productos sin bolsa a una lista de bolsas.

int anadirsinbolsa(struct ListaEnlazada * Lista, struct Producto *Dato);

// Anadir un producto a una lista enlazada. Se agregan de forma ordenada.
int addelementlist(struct ListaEnlazada * Lista, struct Producto * Dato1);

// Eliminar un producto de una lista.

struct Producto *removeelementlist(struct ListaEnlazada *Lista);

// Eliminar una lista enlazada.

int removelist(struct ListaEnlazada * Lista);

// Imprimir una lista de carrito.

void imprimirlista(struct ListaEnlazada *lista);

// Funcion para realizar una impresion de una lista cuyos elementos son
// bolsas.

void imprimirlistabolsa(struct ListaEnlazada *lista);