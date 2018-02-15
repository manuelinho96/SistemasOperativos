/* IMPLEMENTACION DE LAS FUNCIONES DE COLA

Estudiantes:
- Ian Goldberg      # 14-10406
- Manuel Rodriguez  # 13-11223
- David Segura      # 13-11341
*/

#include "cola.h"

/******************** COLAVACIA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Determina si una cola esta vacia
ENTRADA: cola ----> ColaCarrito (Estructura de Cola) 
SALIDA:  int  ----> Entero que indica si la cola esta vacia:
                    1 si lo está, 0 lo contrario */

int colavacia(ColaCarrito *cola){
    if ((*cola).nraiz == NULL) {
        return 1;
    }
    else{
        return 0;
    }
}

/******************** INSERTARNODOCOLA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Inserta un nodo en la cola
ENTRADA: producto ----> Estructura del producto a encolar
         cola     ----> Cola donde se añadira el nodo 
*/

void insertarnodocola(struct Producto *producto, ColaCarrito *cola){
    struct nodocola *nuevo;
    if ((nuevo = malloc(sizeof(struct nodocola)))==NULL) return;
    nuevo->Dato = producto;
    nuevo -> siguiente = NULL;  
    if (colavacia(cola)){
        cola->nraiz = nuevo;
        cola->nfinal = nuevo;
    }
    else{
        cola->nfinal->siguiente = nuevo;
        cola->nfinal = nuevo;
    }
}

/******************** IMPRIMIRCOLA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Imprime los datos de la cola
ENTRADA: cola     ----> Estructura de cola
*/

void imprimircola(ColaCarrito *cola){
    struct nodocola *actual = cola->nraiz;
    while(actual != NULL){
        if(actual->siguiente != NULL ){
            printf("%s - ", actual->Dato->Nombre);
            actual = actual->siguiente;
        }else{
            printf("%s", actual->Dato->Nombre);
            actual = actual->siguiente;
        }
    }
    printf("\n");
}

/******************** LIBERARCOLA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Liberar de la memoria el contenido de una cola
ENTRADA: cola     ----> Estructura de cola
*/

void liberarcola(ColaCarrito *cola){
    struct nodocola *actual = cola->nraiz;
    struct nodocola *borrado;
    while(actual != NULL){
        borrado = actual;
        actual = actual -> siguiente;
        free(borrado);
    }
}

/******************** EXTRAERNODOCOLA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Realiza la operación de desencolar retornado el
             elemento extraído.
ENTRADA: cola ----> ColaCarrito (Estructura de Cola) 
SALIDA:  Dato  ----> struct Producto (retorna NULL si hubo
                     error y retorna la estructura en caso
                     contrario)*/

struct Producto *extraernodocola(ColaCarrito *cola){
    if (!colavacia(cola)){
        struct Producto *Dato = cola->nraiz->Dato;
        struct nodocola *borrado = cola->nraiz;
        if(cola->nraiz == cola->nfinal){
            cola->nraiz = NULL;
            cola->nfinal = NULL;
        }
        else{
            cola->nraiz = cola->nraiz->siguiente;
        }
        free(borrado);
        return Dato;
    }
}