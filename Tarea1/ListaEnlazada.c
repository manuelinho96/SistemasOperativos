/* IMPLEMENTACION DE LAS FUNCIONES DE LISTA ENLAZADA

Estudiantes:
- Ian Goldberg      # 14-10406
- Manuel Rodriguez  # 13-11223
- David Segura      # 13-11341
*/

#include "ListaEnlazada.h"

/******************** INICIALIZE ********************/
/*
TIPO: Funcion 
DESCRIPCION: Inicializa la estructura de lista enlazada
ENTRADA: Lista ----> Lista Enlazada */

void Inicialize(struct ListaEnlazada * Lista){
    Lista->head = NULL;
}

/************************** ANADIRBOLSA **************************/
/*
TIPO: Funcion 
DESCRIPCION: Agrega una bolsa a la lista
ENTRADA: Lista ----> Lista Enlazada a la que se agregara la bolsa
         Bolsa ----> Lista Enlazada que contiene productos
SALIDA:  int (-1 para error y 0 para exito) */

int anadirbolsa(struct ListaEnlazada *Lista, struct ListaEnlazada *Bolsa){
    struct NodoLista *nodo;
    struct NodoLista *actual = Lista->head;
    struct NodoLista *anterior = NULL;
    if ((nodo = malloc(sizeof(struct NodoLista)))==NULL) return -1;
    if ((nodo-> Bolsa = malloc(sizeof(Bolsa)))==NULL) return -1;
    memcpy(nodo-> Bolsa, Bolsa, sizeof(Bolsa));
    nodo->esBolsa = 1;
    nodo->next = NULL;
    if(Lista->head == NULL){
        Lista->head = nodo;
        return 0;
    }
    else{
        while(actual != NULL){
            anterior = actual;
            actual = actual->next;
        }
        anterior->next = nodo;
        return 0;
    }
}

/************************** ANADIRSINBOLSA **************************/
/*
TIPO: Funcion 
DESCRIPCION: Agrega un producto a la lista (USADO PARA EMBOLSAR)
ENTRADA: Lista ----> Lista Enlazada a la que se agregara el producto
         Dato  ----> Producto
SALIDA:  int (-1 para error y 0 para exito) */

int anadirsinbolsa(struct ListaEnlazada * Lista, struct Producto *Dato){
    struct NodoLista *nodo;
    struct NodoLista *actual = Lista->head;
    struct NodoLista *anterior = NULL;
    if ((nodo = malloc(sizeof(struct NodoLista)))==NULL) return -1;
    nodo->Dato = Dato;
    nodo->esBolsa = 0 ;
    nodo->next = NULL;
    if(Lista->head == NULL){
        Lista->head = nodo;
        return 0;
    }
    else{
        while(actual != NULL){
            anterior = actual;
            actual = actual->next;
        }
        anterior->next = nodo;
        return 0;
    }
}

/************************** ADDELEMENTLIST **************************/
/*
TIPO: Funcion 
DESCRIPCION: Agrega un producto a la lista
ENTRADA: Lista ----> Lista Enlazada a la que se agregara el producto
         Dato  ----> Producto
SALIDA:  int (-1 para error y 0 para exito) */

int addelementlist(struct ListaEnlazada * Lista, struct Producto * Dato1){
    struct NodoLista *nodo;
    struct NodoLista *actual = Lista->head;
    struct NodoLista *anterior = NULL;
    if ((nodo = malloc(sizeof(struct NodoLista)))==NULL) return -1;
    nodo->Dato = Dato1;
    nodo->esBolsa = 0;
    if(Lista->head == NULL){
        Lista->head = nodo;
        Lista->head->next = NULL;
        return 0;
    }
    while(actual != NULL && actual->Dato->Peso <= Dato1->Peso){
        anterior = actual;
        actual = actual->next;
    }
    if ( actual == NULL ){
        if (anterior != NULL) anterior->next = nodo;
        else{
            Lista->head = nodo;
        }
        nodo->next = NULL;
        return 0;
    }
    else{
        if (anterior == NULL){
            Lista->head = nodo;
            nodo->next = actual;
            return 0;
        }
        anterior->next = nodo;
        nodo->next = actual;
        return 0;
    }
}

/*********************** REMOVEELEMENTLIST ***********************/
/*
TIPO: Funcion 
DESCRIPCION: Elimina un elemento de la lista y lo retorna
ENTRADA: Lista ----> Lista Enlazada
SALIDA:  Dato  ----> struct Producto */

struct Producto *removeelementlist(struct ListaEnlazada *Lista){
    if (Lista->head != NULL){
        struct Producto *Dato = Lista->head->Dato;
        struct NodoLista *borrado = Lista->head;
        Lista->head = Lista->head->next;
        free(borrado);
        return Dato;
    }
}

/******************** REMOVELIST ********************/
/*
TIPO: Funcion 
DESCRIPCION: Liberar de la memoria el contenido de una lista enlazada
ENTRADA: Lista ----> Lista Enlazada 
SALIDA:  int   ----> entero  */

int removelist(struct ListaEnlazada * Lista){
    struct NodoLista * actual = Lista->head;
    struct NodoLista *borrado;
    while(actual != NULL){
        borrado = actual;
        actual = actual -> next;
        if(borrado->esBolsa == 1) free(borrado->Bolsa);
        free(borrado);
    }
    Lista->head = NULL;
    return 0;
}

/******************** IMPRIMIRLISTA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Imprime los datos de la lista
ENTRADA: lista ----> Lista Enlazada 
*/

void imprimirlista(struct ListaEnlazada *lista){
    struct NodoLista *actual = lista->head;
    while(actual != NULL){
        if(actual->next != NULL){
            printf("%s - ", actual->Dato->Nombre);
            actual = actual->next;
        }
        else{
            printf("%s\n", actual->Dato->Nombre);
            actual = actual->next;
        }
    }
}

/******************** IMPRIMIRLISTABOLSA ********************/
/*
TIPO: Funcion 
DESCRIPCION: Imprime los productos de las bolsas
ENTRADA: lista ----> Lista Enlazada 
*/

void imprimirlistabolsa(struct ListaEnlazada *lista){
    int i = 0;
    struct NodoLista *actual = lista->head;
    while(actual != NULL){
        if(actual->next != NULL && actual->esBolsa == 1){
            printf("Bolsa %d: ", i+1);
            imprimirlista(actual->Bolsa);
            actual = actual->next;
            i++;
        }
        else if (actual->next != NULL && actual->esBolsa != 1) {
            printf("Sin Bolsa: %s\n", actual->Dato->Nombre);
            actual = actual->next;
        }
        else if(actual->next == NULL && actual->esBolsa == 1){
            printf("Bolsa %d: ", i+1);
            imprimirlista(actual->Bolsa);
            actual = actual->next;
            i++;
        }
        else{
            printf("Sin Bolsa: %s", actual->Dato->Nombre);
            actual = actual->next;
        }
    }
    printf("\n");
}