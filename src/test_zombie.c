#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        printf("Fils : Je suis le fils, mon pid interne est %d.\n", pid);
        printf("Fils : Termine !\n");
    }
    else if (pid > 0)
    {
        printf("Pere : Je suis le pere, le pid de mon fils est %d.\n", pid);
        while (1) // Boucle infinie, le père ne termine jamais !
            usleep(1);
    }
    return (0);
}