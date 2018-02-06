struct NodoLista
{
    struct Producto * Dato;
    struct NodoLista * next;
};

typedef struct ListaEnlazada
{
    struct NodoLista * head;
}ListaEnlazada;

void Inicialize(struct ListaEnlazada * Lista)
{
    Lista->head = NULL;
};


int addelementlist(struct ListaEnlazada * Lista, struct Producto * Dato1)
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

struct Producto *removeelementlist(struct ListaEnlazada *Lista){
    if (Lista->head != NULL){
        struct Producto *Dato = Lista->head->Dato;
        struct NodoLista *borrado = Lista->head;
        Lista->head = Lista->head->next;
        free(borrado);
        return Dato;
    }
}

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
    printf("Lista de elementos de la lista: ");
    while(actual != NULL){
        printf("%s - ", actual->Dato->Nombre);
        actual = actual->next;
    }
    printf("\n");
}


