#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
/* waitpid.c - Esperar la terminación de un proceso hijo */
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#ifdef CONFIG_BLOCK	//no funciona en todas las versiones de unix
	#include <linux/fs.h>	//función bdget
#endif
#include <pwd.h>	//función getpwuid
#include <grp.h>	//función getgrgid
#include <sys/dir.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define LEER		0
#define ESCRIBIR	1

void navegar_directorio(const char *name, const char *name2){
    pid_t id_hijo;
    pid_t id_padre;
    DIR *dir;
    struct dirent *entry;
    int descriptor;
    char path[PATH_MAX];
    char pathstring[PATH_MAX];
    FILE *fp;

    if((id_hijo = fork()) != 0){
        if (!(dir = opendir(name))){
            kill(id_hijo,SIGKILL);
        }
        // Concateno el nombre encontrado
        while((entry = readdir(dir)) != NULL){
            if (entry->d_type == DT_DIR) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                snprintf(pathstring, sizeof(pathstring), "%s%s", name2, entry->d_name);
                navegar_directorio(path, pathstring);
            }else {
                snprintf(pathstring, sizeof(pathstring), "%s%s", name2, entry->d_name);
                fp = fopen("archivo de prueba", "a"); // abrimos el archivo
                if(fp == NULL) perror("error al abrir archivo");
                fprintf(fp,"%s\n", pathstring); //escribimos en el archivo
                fclose(fp); //lo cerramos
            }
        }
    }
    else{
        id_padre = getpid();
        while(wait(NULL)>0);
        kill(id_padre,SIGKILL);
    }
}

int main(void) {
    DIR *dir;
    struct dirent *entry;
    int pipedescriptor;
    char path[PATH_MAX] = "";
    char pathstring[PATH_MAX] = "";
    char boolean[1];
    char *pipename = "tuberia2";
    key_t Clave;
	int Id_Semaforo;
	struct sembuf Operacion;

    if (!(dir = opendir("c"))) return -1;
    while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_DIR) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(path, sizeof(path), "%s/%s", "c", entry->d_name);
        snprintf(pathstring, sizeof(pathstring), "%s%s", "c", entry->d_name);
        navegar_directorio(path, pathstring);
        }else {
            printf("Soy archivo\n");
            // Concateno con el nombre del archivo
        }
    }
}