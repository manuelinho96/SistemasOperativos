#include <stdlib.h>

struct Producto
{
    char Nombre[1000];
    double Peso;
    int complejidad;
};

struct NodoLista
{
    struct Producto * Dato;
    struct NodoLista * next;
};

struct ListaEnlazada
{
    struct NodoLista * head;
};

void Inicialize(struct ListaEnlazada * Lista)
{
    Lista->head = NULL;
}

int add(struct ListaEnlazada * Lista, struct Producto * Dato1)
{
    struct NodoLista * nodo;
    nodo->Dato = Dato1;
    struct NodoLista * head = Lista->head;
    if(head == NULL){
        Lista->head = nodo;
        return 0;
    }
    struct NodoLista * actual = head;
    struct NodoLista * anterior;
    while(actual->next != NULL || actual->next->Dato->Peso <= Dato1->Peso ){
        anterior = actual;
        actual = actual->next;
    }
    if(actual->next == NULL){
        if ( actual->next = (nodo *) malloc(sizeof(nodo)) == NULL){
            return -1;
        }
        actual->next->next = NULL;
        actual->next = nodo;
        return 0;
    }
    else{
        anterior->next = nodo;
        nodo->next = actual;
        return 0;
    }
}

int remove(struct ListaEnlazada * Lista, struct NodoLista * Nodo){
    struct NodoLista * head = Lista->head;
    if(head == NULL){
        return 0;
    }
    struct NodoLista * anterior;
    struct NodoLista * actual = head;
    while(actual->next != NULL || actual->next != Nodo){
        anterior = actual;
        actual = actual->next;
    }
    if(actual->next == NULL){
        return 0;
    }
    else{
        anterior->next = actual->next;
        free(actual);
        return 0;
    }
}
int eliminar(struct ListaEnlazada * Lista){
    struct NodoLista * head = Lista->head;
    struct NodoLista * actual = Lista->head;
    struct NodoLista * anterior;
    if(head == NULL){
        return 0;
    }
    while(actual->next != NULL)
    {
        anterior = actual;
        remove(Lista, anterior);
        actual = actual->next;
    }
    remove(Lista, actual);
    return 0;
}
