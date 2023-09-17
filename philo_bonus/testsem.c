#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>

int main()
{
    sem_t   *sem;

    sem = sem_open("/testounet", O_CREAT, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, 25);
    if (!sem)
        return (printf("open rate\n"));

    while (1)
    {
        sem_post(sem);
        printf("j'ai incremente");
    }
}
