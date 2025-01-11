#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3

// общий глобальный счётчик
int shared_counter = 0;

//  обработчик в нити
void* thread_func(void *arg)
{
    // общий локальный счётчик
    int local = 0;
    
    // задержка 
    sleep(abs(5 - (int)arg));

    // информация о нити
    printf("***Thread #%d with ID %#x: shared value is %d, local value is %d\n", 
            (int)arg, pthread_self(), shared_counter++, local++);

    return NULL;
}


int main()
{
    pthread_t th_id;
    int i, err;
 
    for (i = 0; i < NUM_THREADS; i++) {
        // создание нити
        err = pthread_create(&th_id, NULL, thread_func, (void *)i);
        if (err != 0) {
            printf("Error %d\n", err);
            return err;
        } else {
            printf("MAIN: created thread with ID %#x\n", th_id);
        }
    }
    
    // задержка для удобства отладки
    sleep(10);
    return 0;
}

