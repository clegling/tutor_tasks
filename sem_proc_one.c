#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>


int main(int argc, char **argv)
{
    key_t key;
    int semid;
    struct sembuf sops;
    
    // Создание общего ключа доступа к разделяемым ресурсам
    key = ftok("./temp", 'S');
    
    semid = semget(key, 1, 0666 | IPC_CREAT);

    
    // Инициализация семафора номер 0 значением 2
    semctl(semid, 0, SETVAL, (int) 2);
    sops.sem_num = 0;
    sops.sem_flg = 0;

    do {
        sops.sem_op = -2;
        semop(semid, &sops, 1);

        printf("Мои тапки!\n");

        //sops.sem_op = 1;
        //semop(semid, &sops, 1);
    } while (1);

    // Уничтожение семафора
    semctl(semid, 0, IPC_RMID, (int) 0);
    return 0;
}
