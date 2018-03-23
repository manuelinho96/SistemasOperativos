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
#include <getopt.h>


// Mutex
pthread_mutex_t lock;

// Variable globales
int maxlength = 20;

// Director desde el cual se inicia la busqueda
char inicio[PATH_MAX]=".";

// Archivo que contiene el indice
char archivoindice[NAME_MAX]="indice.txt";

// Termino de busqueda
char *termdebusqueda;

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

// Buscador de la tabla de Hash
// Dado un termino de busqueda lo busca en la tabla de hash
// Al entrar en la celda luego verifica que rutas cumplen con el termino
// de busqueda indicado. Por ahora se asume que el nombre de los archivos
// son con - para hacer el split.
void buscarruta(char *termbusq){
    pcelda cp; /* current pointer */

    for(cp = hashtable[stringhash(termbusq)]; cp != NULL; cp = cp->next){
        encontrartermino(cp->ruta, termbusq);
    }
}

// Verifica si un termino de busqueda es encontrado en una ruta.
void encontrartermino(char *ruta, char*termbusq){
    char *filename;
    char *claves;
    filename = strsave(basename(ruta)); //basename devuelve el nombre de un archivo dado una ruta
    claves = strtok(filename,"-.");
    while( claves != NULL ){
        if(strcmp(claves, termbusq) == NULL){
            printf("%s\n", ruta);
        } // Encontre un tembusq.
        claves = strtok(NULL, "-.");
    }
}

// Funcion para cargar el indexador
void *cargartable(void *args){
    pthread_mutex_lock(&lock);
    FILE *indice;
    char *nombre = (char *) args;
    indice = fopen(nombre, "r");
    char *string;
    char *ruta;
    char *termbusq;
    char caracteres[NAME_MAX];
    if (indice == NULL){
        indice = fopen(nombre,"w+");
        if ( indice == NULL ){
            perror("error al crear el archivo");
            exit(1);
        }
    }
    fseek(indice, 0, SEEK_END );
    if (ftell( indice ) == 0 )
    {
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    fseek(indice, 0, SEEK_SET );
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
    fclose(indice);
    printf("termine\n");
    pthread_mutex_unlock(&lock);
    buscarruta(termdebusqueda);
    return NULL;
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

void navegar_directorio(char* routename, int heightvalue){

    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    char *archivoaux;
    char *claves;
    int found;

    if (!(dir = opendir(routename))){
        return;
    }
    heightvalue++;
    while((entry = readdir(dir)) != NULL){
        found = 0;
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                snprintf(path, sizeof(path), "%s/%s", routename, entry->d_name);
                if(heightvalue <= maxlength) navegar_directorio(path, heightvalue);
            } 
            else {
                snprintf(path, sizeof(path), "%s/%s", routename, entry->d_name);
                archivoaux = strsave(entry->d_name);
                claves = strtok(archivoaux, "-.");
                pthread_mutex_lock(&lock);
                while( claves != NULL ){
                    if (!buscar(path, claves)){
                        insertarrutaarchivo(path, claves);
                        claves = strtok(NULL, "-.");
                        if(found == 1) encontrartermino(path, termdebusqueda);
                    }else{
                        claves = strtok(NULL, "-.");
                    }
                }
                pthread_mutex_unlock(&lock);
            }
        }
    return;
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
    int found;

    if (!(dir = opendir(routename))){
        return NULL;
    }
    heightvalue++;
    while((entry = readdir(dir)) != NULL){
        found = 0;
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                snprintf(path, sizeof(path), "%s/%s", routename, entry->d_name);
                if(heightvalue <= maxlength) navegar_directorio(path, heightvalue);
            } 
            else {
                snprintf(path, sizeof(path), "%s/%s", routename, entry->d_name);
                archivoaux = strsave(entry->d_name);
                claves = strtok(archivoaux, "-.");
                pthread_mutex_lock(&lock);
                while( claves != NULL ){
                    if (!buscar(path, claves)){
                        found++;
                        insertarrutaarchivo(path, claves);
                        claves = strtok(NULL, "-.");
                        if(found == 1) encontrartermino(path, termdebusqueda);
                    }else{
                        claves = strtok(NULL, "-.");
                    }
                }
                pthread_mutex_unlock(&lock);
            }
        }
    return NULL;
}

// Declaracion de flags
static struct option long_options[] ={
    {"noupdate",    no_argument,      0, 'u'},
    {"noadd",       no_argument,       0, 'a'},
    {"index",       required_argument, 0, 'i'},
    {"max",         required_argument, 0, 'm'},
    {"dir",         required_argument, 0, 'd'},
    {0, 0, 0, 0}
};

int main(int argc, char *args[]){

    int flags;
    while(flags != -1){
        int option_index = 0;
        flags = getopt_long(argc, args, "uai:m:d:", long_options, &option_index);
        if (flags == -1) break;
        switch (flags) {
            case 'u':
            printf("Indica que no se debe entrar en directorios que ya estén en el índice. No implementado\n");
            break;

            case 'a':
            printf("Indica que no se debe entrar en directorios que no estén en el índice. No implementado\n");
            break;

            case 'i':
            strcpy(archivoindice, optarg);
            break;

            case 'm':
            maxlength = atoi(optarg);
            break;

            case 'd':
            strcpy(inicio, optarg);
            break;

            case '?':
            /* getopt_long already printed an error message. */
            break;

            default:
            abort ();
        }
    }
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
    maketablenull();
    pthread_t cargarindice;
    pthread_t buscarindice;
    pthread_t indezador;
    if (optind < argc)
    {
        termdebusqueda = strsave(args[optind]);
    }
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_create ( &cargarindice, NULL, &cargartable, archivoindice) != 0){
            printf("Error al crear el hilo. \n"); 
            exit(EXIT_FAILURE); 
    }
    parametros *p = malloc(sizeof(parametros));
    p->height = 0;
    strcpy(p->routename, inicio);
    if (pthread_create ( &indezador, NULL, &indizar, p) != 0){
        printf("Error al crear el hilo. \n"); 
        exit(EXIT_FAILURE); 
    }
    pthread_join(cargarindice, NULL);
    pthread_join(indezador, NULL);
    pthread_mutex_destroy(&lock);
}