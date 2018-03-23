#include "tablahash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

// Tabla de 100 slots
#define B 100
static pcelda hashtable[100];

void maketablenull(void){
    int i;
    for (i = 0; i < B; i++){
        hashtable[i] = NULL;
    }
}

unsigned int stringhash(char *string){
    unsigned int h = 0;
    for(int i = 0; *string; string++) h = 131*h + *string;
    return(h%B);
}

pcelda buscar(char *ruta, char *termbusq){
    pcelda cp; /* current pointer */

    for(cp = hashtable[stringhash(termbusq)]; cp != NULL; cp = cp->next){
        if(strcmp(ruta, cp->ruta) == 0){
            return (cp); // Encontre una ruta.
        }
    }
    return (NULL);
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

void buscarruta(char *termbusq){
    pcelda cp; /* current pointer */
    for(cp = hashtable[stringhash(termbusq)]; cp != NULL; cp = cp->next){
        encontrartermino(cp->ruta, termbusq);
    }
}


