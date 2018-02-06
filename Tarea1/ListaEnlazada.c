#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
};


int add(struct ListaEnlazada * Lista, struct Producto * Dato1)
{

    struct NodoLista *nodo;
    struct NodoLista *actual = Lista->head;
    struct NodoLista *anterior = NULL;
    nodo = malloc(sizeof(struct NodoLista));
    nodo->Dato = Dato1;
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
};

int removelist(struct ListaEnlazada * Lista){
    struct NodoLista * actual = Lista->head;
    struct NodoLista *borrado;
    while(actual != NULL){
        borrado = actual;
        actual = actual -> next;
        free(borrado);
    }
    Lista->head = NULL;
}


void imprimirlista(struct ListaEnlazada *lista){
    struct NodoLista *actual = lista->head;
    while(actual != NULL){
        printf("%s - ", actual->Dato->Nombre);
        actual = actual->next;
    }
    printf("\n");
}


int main(){

    struct ListaEnlazada *l;
    l = malloc(sizeof(struct ListaEnlazada));
    Inicialize(l);
    struct Producto *p;
    p = malloc(sizeof(struct Producto));
    strcpy(p->Nombre, "100");
    p->Peso = 100;
    add(l, p);
    p = malloc(sizeof(struct Producto));
    strcpy(p->Nombre, "50");
    p->Peso = 50;
    add(l, p);
    p = malloc(sizeof(struct Producto));
    strcpy(p->Nombre, "30");
    p->Peso = 30;
    add(l,p);
    p = malloc(sizeof(struct Producto));
    strcpy(p->Nombre, "75");
    p->Peso = 70;
    imprimirlista(l);
    add(l, p);
    removelist(l);
    imprimirlista(l);
    add(l, p);
    imprimirlista(l);

}


