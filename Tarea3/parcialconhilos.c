#include <pthread.h>   // Incluimos libreria necesaria para los threads
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <dirent.h>
#include <limits.h>


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

void indizador(char *nombre, int maxlength){
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    char pathstring[PATH_MAX];
    dir = opendir(nombre);


}

void llenartabla(FILE *indice){
    char caracteres[100];
    char *string;
    char *ruta;
    char *termbusq;
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
int buscarruta(char *termbusq){
    pcelda cp; /* current pointer */
    char *filename;
    char *claves;
    int estado = 0;
    for(cp = hashtable[stringhash(termbusq)]; cp != NULL; cp = cp->next){
        filename = strsave(basename(cp->ruta));
        claves = strtok(filename,"-.");
        while( claves != NULL ){
            if(strcmp(claves, termbusq) == NULL){
                estado = 1;
                printf("%s\n", cp->ruta); // Encontre un tembusq.
            } 
            claves = strtok(NULL, "-.");
        }
    }
    return estado;
}

int main(){
    int estado;
    FILE *indice;
    indice = fopen("indice.txt", "r");
    maketablenull();
    llenartabla(indice);
    pthread_mutex_init(&mutex, NULL);
    pthread_t buscador;
    pthread_t indizador;
    estado = buscarruta("manuel");
    fclose(indice);
}



/*<----------------------------------------------------*/

void indizar(const char *name, const char *namestring, 
int maxlength, int height, int includefiles){

    pid_t id_hijo;
    pid_t id_padre;
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    char pathstring[PATH_MAX];
    char archivoaux;
    char claves;

    int maxlengthvalue = maxlength;
    int heightvalue = height;
    int includefilesvalue = includefiles;
    int estado;
    
    if((id_hijo = fork()) != 0){

        if (!(dir = opendir(name))){
            kill(id_hijo,SIGKILL);
        }
        if( maxlengthvalue != heightvalue ){

            while((entry = readdir(dir)) != NULL){
                if (entry->d_type == DT_DIR) {
                    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                    snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                    snprintf(pathstring, sizeof(pathstring), "%s%s", namestring, entry->d_name);
                    heightvalue++;
                    navegar_directorio(path, pathstring, maxlength, heightvalue, includefiles);
                }else {
                    if(includefilesvalue && entry->d_type != DT_DIR){
                        snprintf(pathstring, sizeof(pathstring), "%s%s", namestring, entry->d_name);
                    }
                    else{
                        snprintf(pathstring, sizeof(pathstring), "%s", namestring);
                    }
                    archivoaux = strsave(basename(path));
                    claves = strtok(archivoaux, '-.');
                    while( claves != NULL ){
                        estado =buscarruta(claves);
                        if (estado = 0){
                            insertar(path, claves);
                        }
                        claves = strtok(NULL, "-.");
                    }
    } // Encontre un tembusq.
                        claves = strtok(NULL, "-.");
        }
                }
            }
        }else{
            fp = fopen("caminos.txt", "a");
            if(fp == NULL) perror("error al abrir archivo");
            fprintf(fp,"%s\n", namestring);
            fclose(fp);
        }
    }
    else{
        id_padre = getpid();
        while(wait(NULL)>0);
        exit(0);
    }
}