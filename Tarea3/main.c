#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <getopt.h>
#include <funciones.h>
#include <tablahash.h>


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

// Declaracion de flags
static struct option long_options[] ={
    {"noupdate",    no_argument,      0, 'u'},
    {"noadd",       no_argument,       0, 'a'},
    {"index",       required_argument, 0, 'i'},
    {"max",         required_argument, 0, 'm'},
    {"dir",         required_argument, 0, 'd'},
    {0, 0, 0, 0}
};


// Pametros de indexacion
typedef struct ParametrosIndexar{
    char routename[PATH_MAX];
    int height;
}parametros;

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
    pthread_mutex_unlock(&lock);
    buscarruta(termdebusqueda);
    return NULL;
}

void navegar_directorio(char* routename, int heightvalue){

    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    char *archivoaux;
    char *claves;
    int found;
    int estaenindice;

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
                pthread_mutex_lock(&lock);
                snprintf(path, sizeof(path), "%s/%s", routename, entry->d_name);
                archivoaux = strsave(entry->d_name);
                claves = strtok(archivoaux, "-.");
                estaenindice = 1;
                while( claves != NULL ){
                    if (!buscar(path, claves)){
                        found++;
                        insertarrutaarchivo(path, claves);
                        claves = strtok(NULL, ".-");
                        estaenindice = 0;
                    }else{
                        claves = strtok(NULL, ".-");
                    }
                }
                if(!estaenindice) encontrartermino(path, termdebusqueda);
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
    int estaenindice;

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
                pthread_mutex_lock(&lock);
                snprintf(path, sizeof(path), "%s/%s", routename, entry->d_name);
                archivoaux = strsave(basename(path));
                claves = strtok(archivoaux, "-.");
                estaenindice = 1;
                while( claves != NULL ){
                    if (!buscar(path, claves)){
                        found++;
                        insertarrutaarchivo(path, claves);
                        claves = strtok(NULL, ".-");
                        estaenindice = 0;
                    }else{
                        claves = strtok(NULL, ".-");
                    }
                }
                if(!estaenindice) encontrartermino(path, termdebusqueda);
                pthread_mutex_unlock(&lock);
            }
        }
    return NULL;

}

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
        printf("\n Fallo inicio de mutex \n");
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