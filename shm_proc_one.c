#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>

#define NMAX 256

int main(int argc, char **argv)
{
    key_t key;
    int semid, shmid;
    struct sembuf sops;
    char *shmaddr;
    char str[NMAX];
    
    // Создание общего ключа доступа к разделяемым ресурсам
    key = ftok("./temp", 'S');
    
    semid = semget(key, 1, 0666 | IPC_CREAT);
    

    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    shmaddr = shmat(shmid, NULL, 0);
    
    // Инициализация семафора номер 0 значением 3
    semctl(semid, 0, SETVAL, (int) 0);
    sops.sem_num = 0;
    sops.sem_flg = 0;

    do {
        printf("Введите строку:");
        if (fgets(str, NMAX, stdin) == NULL)
        {
            strcpy(str, "Q");
        }
        
        strcpy(shmaddr, str); 
        
        sops.sem_op = 3;
        semop(semid, &sops, 1);
        
        sops.sem_op = 0;
        semop(semid, &sops, 1);
    } while (str[0] != 'Q');

    // Открепление разделяемой памяти от адресного пространства
    shmdt(shmaddr);

    // Уничтожение разделяемой памяти
    shmctl(shmid, IPC_RMID, NULL); 

    // Уничтожение семафора
    semctl(semid, 0, IPC_RMID, (int) 0);
    return 0;
}