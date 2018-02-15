#ifndef __LISTA__
#define __LISTA__
#include "ListaEnlazada.h"
#endif
#include "globals.h"


// Leer productos de un archivo de entrada.

void LeerProductos(const char *Nombre);

// Imprimir lista de productos en el almacen.

void imprimirproductos();

// Generar un carrito con productos tomados al azar.

int generarcarrito(ListaEnlazada *Carrito);

// Funcion para escribir un logfle de la simulacion.

void writelogfile(int cantidaddecarritos, int *numproductscarrito, int *tiempoclientes, int tiempototal, const char *infile);