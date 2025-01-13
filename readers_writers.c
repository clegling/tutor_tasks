#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

time_t tmstart;

int rc = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t db = PTHREAD_MUTEX_INITIALIZER;

void do_some_work(int nsec) { sleep(nsec); }

void* reader(void * arg)
{
    pthread_mutex_lock(&mutex);
    rc++;
    if (rc == 1) pthread_mutex_lock(&db);
    pthread_mutex_unlock(&mutex);
    
    do_some_work(5);
    
    pthread_mutex_lock(&mutex);
    rc--;
    if (rc == 0) pthread_mutex_unlock(&db);
    pthread_mutex_unlock(&mutex);
    
    printf("---Читатель %#x завершился на %d секунде\n",
            pthread_self(), time(0) - tmstart);
    return NULL;
}

void* writer(void * arg)
{
    pthread_mutex_lock(&db);
    do_some_work(12);
    pthread_mutex_unlock(&db);

    printf("---Писатель %#x завершился на %d секунде\n",
        pthread_self(), time(0) - tmstart);
    return NULL;
}
int main()
{
    int nr, nw, bFlag;
    pthread_t th_id;
    printf(">>Введите число читателей и писателей:\n");
    scanf("%u %u", &nr, &nw);
    tmstart = time(0);
    bFlag = !(nr > 0);

    while (nr > 0 || nw > 0) {
        pthread_create(&th_id, NULL, bFlag ? writer : reader, NULL);
        printf("+++%s %#x запущен на %d секунде\n", bFlag ?
            "Писатель" : "Читатель", th_id, time(0) - tmstart);
       
        bFlag = bFlag ? (nw--, nr == 0) : (nr--, nw);
    }

    for (;;) sleep(5);
    return 0;
}