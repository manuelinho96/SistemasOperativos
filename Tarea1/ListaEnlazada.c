struct NodoLista
{
    struct Producto **Bolsa;
    struct Producto * Dato;
    struct NodoLista * next;
    int esBolsa;
};

typedef struct ListaEnlazada
{
    struct NodoLista * head;
}ListaEnlazada;

void Inicialize(struct ListaEnlazada * Lista)
{
    Lista->head = NULL;
};



int anadirbolsa(struct ListaEnlazada * Lista, struct Producto **Bolsa){
    struct NodoLista *nodo;
    struct NodoLista *actual = Lista->head;
    struct NodoLista *anterior = NULL;
    nodo = malloc(sizeof(struct NodoLista));
    nodo->Bolsa = Bolsa;
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


int addelementlist(struct ListaEnlazada * Lista, struct Producto * Dato1)
{

    struct NodoLista *nodo;
    struct NodoLista *actual = Lista->head;
    struct NodoLista *anterior = NULL;
    nodo = malloc(sizeof(struct NodoLista));
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
    while(actual != NULL){
        if(actual->next != NULL){
            printf("%s - ", actual->Dato->Nombre);
            actual = actual->next;
        }
        else{
            printf("%s", actual->Dato->Nombre);
            actual = actual->next;
        }
    }
    printf("\n");
}

void imprimirlistabolsa(struct ListaEnlazada *lista){
    int i = 0;
    struct NodoLista *actual = lista->head;
    while(actual != NULL){
        if(actual->next != NULL && actual->esBolsa == 1){
            printf("Bolsa numero: %d ", i);
            //imprimirlista(actual->Bolsa);
            actual = actual->next;
            i++;
        }
        else if (actual->next != NULL && actual->esBolsa != 1) {
            printf("-%s", actual->Dato->Nombre);
            actual = actual->next;
        }
        else if(actual->next == NULL && actual->esBolsa == 1){
            printf("Bolsa numero: %d ", i);
            //imprimirlista(actual->Bolsa);
            actual = actual->next;
            i++;
        }
        else{
            printf("%s", actual->Dato->Nombre);
            actual = actual->next;
        }
    }
    printf("\n");
}


