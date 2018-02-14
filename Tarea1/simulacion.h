#ifndef __LISTA__
#define __LISTA__
#include "ListaEnlazada.h"
#endif

const char *modalidad = "Interactiva";
int carritoEnCola = 3;
int maxproductscarrito = 30;
int maxbt = 200;
float velocidadcajera = 1;
int velocidadembolsador = 4;
int tiempofacturacion = 130;
int maxareaembolsado = 150;
int maxbolsa = 120;
int cantidaddeproductos;
int cantidaddecarritos;
Producto **Productos;

// Leer productos de un archivo de entrada.

struct Producto **LeerProductos(const char *Nombre);

// Imprimir lista de productos en el almacen.

void imprimirproductos();

// Generar un carrito con productos tomados al azar.

int generarcarrito(ListaEnlazada *Carrito);

// Funcion para escribir un logfle de la simulacion.

void writelogfile(int cantidaddecarritos, int *numproductscarrito, int *tiempoclientes, int tiempototal, const char *infile);