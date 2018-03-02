/* IMPLEMENTACION DE LA NAVEGACION DE DIRECTORIOS

Estudiantes:
- Ian Goldberg      # 14-10406
- Manuel Rodriguez  # 13-11223
- David Segura      # 13-11341
*/

#include "navdirectory.h"

/****************** NAVEGAR_DIRECTORIO ******************/
/*
TIPO: Funcion 
DESCRIPCION: Dado un nombre de directorio, explora los
             directorios hijos.
ENTRADA: name ----> Ruta de un directorio
		 namestring ----> Ruta de un directorio sin /.
         maxlength ----> Maxima altura de un arbol.
         height ----> Altura acumulada por la navegacion del directorio.
         includefiles ----> Booleano para determinar si se incluye
         un archivo en la concatenacion de string o no.
*/

void navegar_directorio(const char *name, const char *namestring, 
int maxlength, int height, int includefiles){

    pid_t id_hijo;
    pid_t id_padre;
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    char pathstring[PATH_MAX];
    FILE *fp;
    int maxlengthvalue = maxlength;
    int heightvalue = height;
    int includefilesvalue = includefiles;
    
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
                    fp = fopen("caminos.txt", "a");
                    if(fp == NULL) perror("error al abrir archivo");
                    fprintf(fp,"%s\n", pathstring);
                    fclose(fp);
                }
            }
        }else{
            if (height == 0) kill(id_hijo,SIGKILL);
            else{
                fp = fopen("caminos.txt", "a");
                if(fp == NULL) perror("error al abrir archivo");
                fprintf(fp,"%s\n", namestring);
                fclose(fp);
            }
        }
    }
    else{
        id_padre = getpid();
        while(wait(NULL)>0);
        exit(0);
    }
}