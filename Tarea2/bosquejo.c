#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
/* waitpid.c - Esperar la terminación de un proceso hijo */
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h> 
#ifdef CONFIG_BLOCK	//no funciona en todas las versiones de unix
	#include <linux/fs.h>	//función bdget
#endif
#include <pwd.h>	//función getpwuid
#include <grp.h>	//función getgrgid
#include <sys/dir.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define LEER		0
#define ESCRIBIR	1

void navegar_directorio(const char *name){
    pid_t id_hijo;
    DIR *dir;
    struct dirent *entry;

    if((id_hijo = fork()) != 0){
        if (!(dir = opendir(name))){
            kill(id_hijo,SIGKILL);
        }
        // Concateno el nombre encontrado
        while((entry = readdir(dir)) != NULL){
            if (entry->d_type == DT_DIR) {
                char path[1024];
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                printf("%s\n", path);
                navegar_directorio(path);
            }else {
                printf("llegue al archivo %s\n", entry->d_name);
                kill(id_hijo,SIGKILL);
                // Concateno con el nombre del archivo
            }
        }
    }
    else{
        while(wait(NULL)>0);
    }
}



int main(void) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir("a"))) return;
    while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_DIR) {
        char path[1024];
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(path, sizeof(path), "%s/%s", "a", entry->d_name);
        navegar_directorio(path);
        }else {
            printf("Soy archivo\n");
            // Concateno con el nombre del archivo
        }
    }
}