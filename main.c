#include "navdirectory.h"

int main(int argc, char *argv[]){
    char *cwd;
    char cwdaux[PATH_MAX];
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX] = "";
    char pathstring[PATH_MAX] = "";
    int maxlength = 20;
    int height = 0;
    int includefiles = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            if(i+1 <= argc) cwd = argv[i+1];

        }
        else if (strcmp(argv[i], "-m") == 0){
            if(i+1 <= argc) maxlength = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "-f") == 0){
            includefiles = 1;
        }
    }

    if ( argc == 1 ){
        getcwd(cwdaux, sizeof(cwdaux));
        if (!(dir = opendir(cwdaux))){
            printf("Error al abrir el directorio raiz\n");
            return -1;
        }
    }else{
        if (!(dir = opendir(cwd))){
            printf("Error al abrir el directorio raiz\n");
            return -1;
        }
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(path, sizeof(path), "%s/%s", cwd, entry->d_name);
        snprintf(pathstring, sizeof(pathstring), "%s%s", cwd, entry->d_name);
        height = 0;
        navegar_directorio(path, pathstring, maxlength, height, includefiles);
        }else {
            printf("Error, el archivo no es la raiz de un directorio.");
        }
    }
}