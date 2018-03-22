#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <pthread.h>   // Incluimos libreria necesaria para los threads
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sched.h>
#include <dirent.h>


// Variable globales
int maxlength;

// Estructura de las celdas de la tabla
typedef struct celda
{
    char *ruta;
    struct celda *next;
} tcelda, *pcelda;

// Pametros de indexacion
typedef struct ParametrosIndexar{
    char routename[PATH_MAX];
    int height;
}parametros;

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
    unsigned int h = 0;
    for(int i = 0; *string; string++) h = 131*h + *string;
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

// Buscador de la tabla de 
// Dado un termino de busqueda lo busca en la tabla de hash
// Al entrar en la celda luego verifica que rutas cumplen con el termino
// de busqueda indicado. Por ahora se asume que el nombre de los archivos
// son con - para hacer el split.
int buscarruta(char *termbusq){
    pcelda cp; /* current pointer */
    char *filename;
    char *claves;
    int foundroute = 0;

    for(cp = hashtable[stringhash(termbusq)]; cp != NULL; cp = cp->next){
        filename = strsave(basename(cp->ruta)); //basename devuelve el nombre de un archivo dado una ruta
        claves = strtok(filename,"-.");
        while( claves != NULL ){
            if(strcmp(claves, termbusq) == NULL){
                printf("%s\n", cp->ruta);
                foundroute++;
            } // Encontre un tembusq.
            claves = strtok(NULL, "-.");
        }
    }
    return foundroute;
}

// Funcion para cargar el indexador
void *cargartable(void *args){
    FILE *indice;
    char *nombre = (char *) args;
    indice = fopen(nombre, "r");
    char *string;
    char *ruta;
    char *termbusq;
    char caracteres[NAME_MAX];
    if (indice == NULL){
        exit(1);
    }
    else{
        while ( !feof(indice) ){
            fgets(caracteres,NAME_MAX,indice);
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
    fclose(indice);
    return NULL;
}

void navegar_directorio(char* routename, int heightvalue){

    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    char *archivoaux;
    char *claves;
    if( maxlength != heightvalue ){
        if (!(dir = opendir(routename))){
            return NULL;
        }
        while((entry = readdir(dir)) != NULL){
            if (entry->d_type == DT_DIR) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                    heightvalue++;
                    snprintf(path, sizeof(path), "%s/%s/", routename, entry->d_name);
                    navegar_directorio(path, heightvalue);
            } 
                else {
                    snprintf(path, sizeof(path), "%s%s", routename, entry->d_name);
                    archivoaux = strsave(entry->d_name);
                    claves = strtok(archivoaux, "-.");
                    while( claves != NULL ){
                        if (!buscar(path, claves)){
                            printf("No esta en la tabla y se agrega\n");
                            printf("%s %s\n", path, claves);
                            insertar(path, claves);
                        }
                        claves = strtok(NULL, "-.");
                    }
                }
        }
    }
    return NULL;

}

void *indizar(void *args){

    
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    char *archivoaux;
    char *claves;
    parametros *p = (parametros *) args;
    char *routename = (char *) p->routename;
    int heightvalue = (int) p->height;
    if( maxlength != heightvalue ){
        if (!(dir = opendir(routename))){
            return NULL;
        }
        while((entry = readdir(dir)) != NULL){
            if (entry->d_type == DT_DIR) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                    heightvalue++;
                    snprintf(path, sizeof(path), "%s/%s/", routename, entry->d_name);
                    navegar_directorio(path, heightvalue);
            } 
                else {
                    snprintf(path, sizeof(path), "%s/%s", routename, entry->d_name);
                    archivoaux = strsave(entry->d_name);
                    claves = strtok(archivoaux, "-.");
                    while( claves != NULL ){
                        if (!buscar(path, claves)){
                            printf("No esta en la tabla y se agrega\n");
                            printf("%s %s\n", path, claves);
                            insertar(path, claves);
                        }
                        claves = strtok(NULL, "-.");
                    }
                }
        }
    }
    return NULL;
}

int main(){

    maxlength = 20;
    char nombre[200] = "indice.txt";
    maketablenull();
    pthread_t cargarindice;
    pthread_t buscarindice;
    pthread_t indezador;
    if (pthread_create ( &cargarindice, NULL, &cargartable, nombre) != 0){
        printf("Error al crear el hilo. \n"); 
        exit(EXIT_FAILURE); 
    }
    pthread_join(cargarindice, NULL);
    parametros *p = malloc(sizeof(parametros));
    p->height = 0;
    strcpy(p->routename, ".");
    if (pthread_create ( &indezador, NULL, &indizar, p) != 0){
        printf("Error al crear el hilo. \n"); 
        exit(EXIT_FAILURE); 
    }
    pthread_join(indezador, NULL);
    printf("resultado de buscar xdxd\n");
    buscarruta("xdxd");
    
}