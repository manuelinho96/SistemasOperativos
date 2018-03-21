#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

/* // Nodo de claves asociadas a una ruta.
typedef struct nodoclave{
    char *clave;
    struct clavescelda *next;
}nodocelda;

// Lista de claves
typedef struct ListaClaves
{
    nodocelda *head;
}ListaClaves;

// Inicializar lista de claves
void inicializarlistaclave(ListaClaves * Lista)
{
    Lista->head = NULL;
}; */


// Estructura de las celdas de la tabla
typedef struct celda
{
    char *ruta;
    struct celda *next;
} tcelda, *pcelda;

// Tabla de 100 slots
#define B 100
static pcelda hashtable[100];

// Crear tabla vacia
void maketablenull(void){
    int i;
    for (i = 0; i < B; i++){
        hashtable[i] = NULL;
    }
}

// Funcion de hash. Propuesta por Brian Kernighan y Dennis Ritchie
unsigned int stringhash(char *string){
    int i;
    unsigned int h = 0;
    for(i = 0; *string; string++) h = 131*h + *string;
    return(h%B);
}

// Buscar si una ruta esta en la tabla
pcelda buscar(char *ruta, char *termbusq){
    pcelda cp; /* current pointer */

    for(cp = hashtable[stringhash(termbusq)]; cp != NULL; cp = cp->next){
        if(strcmp(ruta, cp->ruta) == 0){
            return (cp); // Encontre una ruta.
        }
    }
    return (NULL);
}

// Insertar ruta a la tabla
char *strsave(char *s)
{ char *p;
    if (( p = malloc(strlen(s) + 1)) != NULL)
    strcpy(p, s);
    return (p);
}

pcelda insertar(char *ruta, char*termbusq)
{   pcelda cp /* current pointer */;
    int hval;
    if (( cp = buscar(ruta, termbusq)) == NULL)
    {
        cp = ( pcelda ) malloc(sizeof ( tcelda ));
        if (cp == NULL) return (NULL);
        if (( cp -> ruta  = strsave(ruta)) == NULL ) return (NULL);
        hval = stringhash(termbusq);
        cp -> next = hashtable[hval];
        hashtable[hval] = cp;
        return (cp);
    }
    else return (NULL);
}

// Buscador de la tabla de hash
void buscarruta(char *termbusq){
    pcelda cp; /* current pointer */
    char *filename;
    char *claves;

    for(cp = hashtable[stringhash(termbusq)]; cp != NULL; cp = cp->next){
        filename = strsave(basename(cp->ruta));
        claves = strtok(filename,"-.");
        while( claves != NULL ){
            if(strcmp(claves, termbusq) == NULL) printf("%s\n", cp->ruta); // Encontre un tembusq.
            claves = strtok(NULL, "-.");
        }
    }
}

int main(){
    FILE *indice;
    indice = fopen("indice.txt", "r");
    char caracteres[100];
    char *string;
    char *ruta;
    char *termbusq;
    maketablenull();

    if (indice == NULL){
        exit(1);
    }
    else{
        while ( !feof(indice) ){
            fgets(caracteres,1000,indice);
            string = strtok (caracteres," ");
            ruta = strsave(string);
            while (string != NULL){
                if (string[strlen(string)-1] == '\n') string[strlen(string)-1] = '\0';
                termbusq = strsave(string);
                string = strtok (NULL, " ");
            }
            insertar(ruta, termbusq);
        }
    }
    buscarruta("manuel");
    fclose(indice);
}