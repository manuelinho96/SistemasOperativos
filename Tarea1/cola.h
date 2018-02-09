struct nodocola {
    struct Producto *Dato;
    struct nodocola *siguiente;
};

typedef struct Cola{
    struct nodocola *nraiz;
    struct nodocola *nfinal;
}ColaCarrito;

void iniciarcola(ColaCarrito * cola){
    cola->nraiz = NULL;
    cola->nfinal = NULL;
};

int colavacia(ColaCarrito *cola){
    if ((*cola).nraiz == NULL) {
        return 1;
    }
    else{
        return 0;
    }
}

void insertarnodocola(struct Producto *producto, ColaCarrito *cola){
    struct nodocola *nuevo;
    nuevo = malloc(sizeof(struct nodocola));
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

void liberarcola(ColaCarrito *cola){
    struct nodocola *actual = cola->nraiz;
    struct nodocola *borrado;
    while(actual != NULL){
        borrado = actual;
        actual = actual -> siguiente;
        free(borrado);
    }
}

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