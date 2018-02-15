/* IMPLEMENTACION DE LA ESTRUCTURA DE DATOS LISTA ENLAZADA

Estudiantes:
- Ian Goldberg		# 14-10406
- Manuel Rodriguez	# 13-11223
- David Segura		# 13-11341
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __PRODUCTOS__
#define __PRODUCTOS__
#include "producto.h"
#endif

/************************ NODOLISTA ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de un nodo que contendra tres
estructuras para conformar una lista de bolsas o producto
y un entero que indica que si el elemento es una bolsa o
un producto*/

struct NodoLista{
    struct ListaEnlazada *Bolsa;
    struct Producto * Dato;
    struct NodoLista * next;
    int esBolsa;
};

/************************ LISTAENLAZADA ************************/
/*
TIPO: Estructura de datos
DESCRIPCION: Implementacion de una estructura que contendra una
estructura de un nodo para la simulacion de lista enlazada*/

typedef struct ListaEnlazada{
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