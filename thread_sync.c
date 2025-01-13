#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define N_SIZE 10

char str[N_SIZE + 1];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* fThread(void * arg)
{
    printf("Start Thread ID %#x\n", pthread_self());
    int err = pthread_mutex_unlock(&mutex);
    if (err != 0) printf("Ошибка pthread_mutex_unlock %#x\n", pthread_self());

    int iPos = strlen(str);
    str[iPos] = 'A' + iPos;
    printf("Result %s\n", str);

    err = pthread_mutex_lock(&mutex);
    if (err != 0) printf("Ошибка pthread_mutex_unlock %#x\n", pthread_self());
    printf("Finish Thread ID %#x\n", pthread_self());
    return NULL;
}

int main()
{
    pthread_t th_id;
    int i;

    memset(str, 0, N_SIZE + 1);

    int err = pthread_mutex_lock(&mutex);
    printf("Thread ID %#x\n", pthread_self());
    if (err != 0) printf("Ошибка pthread_mutex_unlock %#x\n", pthread_self());
    for (i = 0; i < N_SIZE; i++) {
        pthread_create(&th_id, NULL, fThread, NULL);
    }
    sleep(5);
    printf("%s\n", str);
    return 0;
}