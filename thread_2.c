#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

// функция-обработчик в нити
void* thread_func(void *arg)
{
    sleep(1);
    return NULL;
    //pthread_exit(NULL);
}


int main()
{
    pthread_t th_id;
    void *pret;
    
    // создание нити - похоже на fork()
    pthread_create(&th_id, NULL, thread_func, NULL);
    time_t tm_start = time(0);

    // ожидаем завершения нити с id th_id (код завершения в pret)
    // блокирующая операция - похоже на waitpid()
    pthread_join(th_id, &pret);
    printf("Thread %#x execution time = %u, status = %#x\n", 
            th_id, time(0) - tm_start, pret);
    return 0;
}
