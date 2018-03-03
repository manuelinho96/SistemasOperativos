/* MAIN DEL PROGRAMA

Estudiantes:
- Ian Goldberg      # 14-10406
- Manuel Rodriguez  # 13-11223
- David Segura      # 13-11341
*/

#include "navdirectory.h"
#include "palindromos.h"

int main(int argc, char *argv[]){
    char *cwd;
    char *buf;
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX] = "";
    char pathstring[PATH_MAX] = "";
    int maxlength = 20;
    int height = 0;
    int includefiles = 0;
    FILE *archivo;
    char caracter[PATH_MAX];
    int existepalindromo = 0;
    long size;
    int flagd = 0;

    archivo = fopen("caminos.txt","w");
    if( archivo == NULL){
        perror("Error de apertura del archivo.");
    }
    fclose(archivo);

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            if(i+1 <= argc){
                cwd = argv[i+1];
                flagd = 1;
            }
            else{
                printf("No se introdujo un directorio\n");
                return -1;
            }

        }
        else if (strcmp(argv[i], "-m") == 0){
            if(i+1 <= argc) maxlength = atoi(argv[i+1]);
            else{
                printf("No se introdujo un maximo de altura\n");
                return -1;
            }
        }
        else if (strcmp(argv[i], "-f") == 0){
            includefiles = 1;
        }
    }

    if ( flagd == 0 ){
        size = PATH_MAX;
        if ((buf = (char *)malloc((size_t)size)) != NULL) cwd = getcwd(buf, (size_t)size);
    }
    if (!(dir = opendir(cwd))){
        printf("Error al abrir el directorio raiz\n");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(path, sizeof(path), "%s/%s", cwd, entry->d_name);
        snprintf(pathstring, sizeof(pathstring), "%s%s", cwd, entry->d_name);
        height = 2;
        navegar_directorio(path, pathstring, maxlength, height, includefiles);
        }else {
            if(includefiles){
                snprintf(pathstring, sizeof(pathstring), "%s%s", cwd, entry->d_name);
                archivo = fopen("caminos.txt", "a");
                if(archivo == NULL) perror("error al abrir archivo");
                fprintf(archivo,"%s\n", pathstring);
                fclose(archivo);
            }
        }
    }

    archivo = fopen("caminos.txt","r");
    if (archivo == NULL){
        perror("Error de apertura del archivo.");
    }
    else{
        while(fgets(caracter,sizeof(caracter),archivo) != NULL){
			existepalindromo += palindromospares(caracter);
			existepalindromo += palindromosimpares(caracter);
        }
    }
    fclose(archivo);
    if( !existepalindromo ){
        printf("No existen palindromos.\n");
    }
    return 0;
}