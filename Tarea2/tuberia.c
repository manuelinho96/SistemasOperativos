#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main(void)
{
    char buf[256];
    int num, fd;
    pid_t pid;

    if (mkfifo(FIFO_NAME, 0666) < 0)
        perror("mkfifo");

    pid = fork();
    if (pid == 0)
    {
        printf("child - waiting for readers...\n");
        if ((fd = open(FIFO_NAME, O_WRONLY)) < 0)
            perror("child - open");

        printf("child - got a reader -- type some stuff\n");
        while (fgets(buf, sizeof(buf), stdin), !feof(stdin))
        {
            if ((num = write(fd, buf, strlen(buf))) < 0)
                perror("child - write");
            else
                printf("child - wrote %d bytes\n", num);
        }

        close(fd);
        exit(0);
    }
    else
    {
        printf("parent - waiting for writers...\n");
        if ((fd = open(FIFO_NAME, O_RDONLY)) < 0)
            perror("parent - open");

        printf("parent - got a writer\n");
        do
        {
            if ((num = read(fd, buf, sizeof(buf))) < 0)
                perror("parent - read");
            else
            {
                buf[num] = '\0';
                printf("parent - read %d bytes: \"%s\"\n", num, buf);
            }
        } while (num > 0);

        close(fd);
        wait(0);
    }

    unlink(FIFO_NAME);
    return 0;
}