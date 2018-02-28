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

void main(){
    DIR *dir;
    FILE *fp;
    char path[PATH_MAX];
    for(int i = 0;i<500;i++){
        snprintf(path, sizeof(path), "c/%d/%d/%d.txt", i,i,i);
        //mkdir(path,0777);
        fp=fopen(path, "w+");
        fclose(fp);
    }
}