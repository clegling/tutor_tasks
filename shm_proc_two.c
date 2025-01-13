/* необходимо корректно определить существование ресурса,
если он есть - подключиться */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

#define NMAX 256

int main(int argc, char **argv)
{
    key_t key;
    int semid, shmid;
    struct sembuf sops;
    char *shmaddr;
    char str[NMAX];
    
    key = ftok("./temp",'S');
    
    semid = semget(key, 1, 0666 | IPC_CREAT);

    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    shmaddr = shmat(shmid, NULL, 0);

    sops.sem_num = 0;
    sops.sem_flg = 0;

    do
    {
        printf("Waiting… \n");

        // semop != 0, то блокировать, пока sem_val + sem_op < 0
        // semop == 0, то блокировать, пока семафор не обнулится
        sops.sem_op = -2;
        semop(semid, &sops, 1);

        
        // критическая секция - работа с разделяемой памятью
        strcpy(str, shmaddr);

        if (str[0] == 'Q')
        {
            shmdt(shmaddr);
        }        

        sops.sem_op = 1;
        semop(semid, &sops, 1);
        printf("Read from shared memory: %s\n", str);
    } while (str[0] != 'Q');
    return 0;
}