#include <dirent.h>


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