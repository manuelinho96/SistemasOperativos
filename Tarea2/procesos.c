/* waitpid.c - Esperar la terminación de un proceso hijo */
#include <stdio.h>
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

int main ()
    {
    pid_t id_padre;	/* PID del proceso padre */
    pid_t id_hijo;	/* PID del proceso hijo */
    int   estado;	/* Estado de salida */
    struct stat nodo;
    DIR *dir;
    struct dirent *ent;

    int descr, longmens, i;
    char mensaje[100];
    unlink ("tuberia");
    mkfifo ("tuberia", 0);

    sprintf (mensaje, "Un saludo desde el proceso %d", getpid ());
    longmens = strlen (mensaje) + 1;

    printf ("Ejemplo de waitpid.\n");
    printf ("Inicio proceso padre. PID=%d\n", getpid ());
    id_padre = getpid ();
    descr = open ("tuberia", O_WRONLY);
    if ((id_hijo = fork ()) == 0)
    {
    	/* Proceso hijo */
/*         if (stat("s", &nodo) == -1){
            printf("Error al leer el directorio\n");
            exit (1);
        }
        if (nodo.st_mode & S_IFDIR){
            while ((ent = readdir (dir)) != NULL) {
                printf ("%s\n", ent->d_name);
            }
            closedir (dir);
        } */
        if ((dir = opendir ("s")) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {
                if(strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0) opendir(ent->d_name);
        }
        closedir (dir);
        } else {
            /* could not open directory */
            perror ("");
            return EXIT_FAILURE;
        }
        write (descr, mensaje, longmens);
        sleep(6);
        printf ("Inicio proceso hijo. PID=%d, PPID=%d\n",
        getpid (), id_padre);
        printf ("Salida proceso hijo. PID=%d\n", getpid ());
        exit (getpid () > id_padre);        /* 1, si PID > PPID */
    }
    else
        {
        write (descr, mensaje, longmens);
        signal (SIGINT, SIG_IGN);        /* Ignorar CTRL-C */
        while (waitpid (id_hijo, &estado, 0) != id_hijo);
        if (WIFSIGNALED (estado))
            printf ("El proceso hijo ha recibido la señal %d\n", WTERMSIG (estado));
        if (WIFEXITED (estado))
           {
           printf ("Estado de salida del proceso hijo: %d\n", WEXITSTATUS (estado));
           if (WEXITSTATUS (estado) == 1)
               printf ("PID hijo > PID padre.\n");
           else
               printf ("PID padre > PID hijo.\n");
           }
        printf ("Fin del proceso %d\n", getpid ());
        exit (0);
    }
}