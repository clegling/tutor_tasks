/* необходимо корректно определить существование ресурса,
если он есть - подключиться */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    key_t key;
    int semid;
    struct sembuf sops;
    
    key = ftok("./temp",'S');
    
    semid = semget(key, 1, 0666 | IPC_CREAT);

    sops.sem_num = 0;
    sops.sem_flg = 0;

    do
    {
        printf("Нет, мои тапки!\n");
        sleep(3);
        // semop != 0, то блокировать, пока sem_val + sem_op < 0
        // semop == 0, то блокировать, пока семафор не обнулится
        sops.sem_op = 2;
        semop(semid, &sops, 1);

        //sops.sem_op = 1;
        //semop(semid, &sops, 1);
    } while (1);
    return 0;
}