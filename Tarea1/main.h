#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cola.h"
#define __LISTA__
#include "ListaEnlazada.h"
#include "globals.h"
#include "simulacion.h"
#include "configuracion.h"
#include "stack.h"
#include <time.h>
#include <math.h>

// Menu del programa principal.

void menu();

// Funcion que ejecuta la simulacion de un carrito.
void simulacion(ListaEnlazada *Carrito,ColaCarrito *BandaT, Stack *Pila, 
ListaEnlazada *Bolsas,const char *modalidad,int numerocarrito,int *numerocliente);

// Funcion para mover elementos a la banda transportadora.
void moveralabanda(ListaEnlazada *Carrito, ColaCarrito *BandaT, int *volumen);

// Funcion para llenar una bolsa
void embolsar(Stack *Pila, ListaEnlazada *Bolsa);