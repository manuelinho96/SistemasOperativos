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

struct Archivo{
    char nombrearchivo[256];
}typedef filename;

char mensajepipe[255];

void listdir(const char *name){

}

void crearproceso(int *descriptores){
    if(fork() == 0){
        // Codigo de proceso Hijo
        printf("segundo\n");
        close (descriptores[ESCRIBIR]);
        read (descriptores[LEER], mensajepipe, 255);
        printf("Lei esto %s\n", mensajepipe);
        close(descriptores[LEER]);
        sleep(5);
    }
}


int main(void) {

    pid_t id_padre;	/* PID del proceso padre */
    pid_t id_hijo;	/* PID del proceso hijo */
    int descriptores[2];
    int   estado;	/* Estado de salida */
    int mensaje;
    DIR *dir;
    struct dirent *entry;

    if( pipe(descriptores) != 0 ) return 1;

    // Codigo del proceso padre
    printf("primero\n");
    crearproceso(descriptores);
    crearproceso(descriptores);
    if (!(dir = opendir("a"))) return;
    close (descriptores[LEER]);
    write (descriptores[ESCRIBIR], "s", strlen("s"));
    close (descriptores[ESCRIBIR]);
    wait(NULL);
    printf("mi hijo termino\n");    

/*     if ( (id_hijo = fork()) == 0 ){
        // Codigo de proceso Hijo
        printf("segundo\n");
        close (descriptores[ESCRIBIR]);
        mensaje = read (descriptores[LEER], mensajepipe, 255);
        printf("Lei esto %s\n", mensajepipe);
        close(descriptores[LEER]);
        sleep(5);

    } */
/*     else{
        // Codigo del proceso padre
        printf("primero\n");
        if (!(dir = opendir("a"))) return;
        close (descriptores[LEER]);
        write (descriptores[ESCRIBIR], "s", strlen("s"));
        close (descriptores[ESCRIBIR]);
        while(wait(NULL)>0);
        printf("mi hijo termino\n");
    } */
    //listdir("s");
    return 0;
}

/* void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
} */