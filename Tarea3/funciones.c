#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <limits.h>

extern char archivoindice[NAME_MAX];

char *strsave(char *s)
{ char *p;
    if (( p = malloc(strlen(s) + 1)) != NULL)
    strcpy(p, s);
    return (p);
}


void insertarrutaarchivo(char *path, char *claves){
    FILE *indice;
    indice = fopen(archivoindice,"a");
    if ( indice == NULL ){
        return;
    }
    fprintf(indice, "%s %s\n", path, claves);
    fclose(indice);
}

void encontrartermino(char *ruta, char*termbusq){
    char *filename;
    char *claves;
    filename = strsave(basename(ruta)); //basename devuelve el nombre de un archivo dado una ruta
    claves = strtok(filename,"-.");
    while( claves != NULL ){
        if(strcmp(claves, termbusq) == 0){
            printf("%s\n", ruta);
        } // Encontre un tembusq.
        claves = strtok(NULL, "-.");
    }
}