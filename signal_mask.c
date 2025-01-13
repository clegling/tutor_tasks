#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    sigset_t sigset;
    int fl;
    sigemptyset(&sigset);
    printf("Добавить SIGINT к текущей маске? (yes - 1, no - 0) \n");
    scanf("%d", &fl);
    if (fl) {
        sigaddset(&sigset, SIGINT);
        sigprocmask(SIG_BLOCK, &sigset, NULL);
    }

    printf("Послать SIGINT? (yes - 1, no - 0)\n");
    scanf("%d", &fl);

    if (fl) kill(getpid(), SIGINT);

    /* получаем сигнальную маску процесса. Так как второй
    аргумент NULL, то первый аргумент игнорируется */
    if (sigprocmask(SIG_BLOCK, NULL, &sigset) == -1)
    {
        printf("Ошибка при вызове sigprocmask()\n");
        return -1;
    } 
    else if (sigismember(&sigset, SIGINT)) 
    {
        printf("Сигнал SIGINT заблокирован! \n");
        sigemptyset(&sigset);
        
        /*узнаем сигналы, ожидающие доставки */
        if (sigpending(&sigset) == -1)
        {
            printf("Ошибка при вызове sigpending()\n");
            return -1;
        }
        /*проверяем наличие сигнала SIGINT в маске*/
        printf("Сигнал SIGINT %s\n”=",
                sigismember(&sigset,SIGINT) ? 
                "ожидает доставки" : 
                "не ожидает доставки");
    }
    else 
        printf("Сигнал SIGINT не заблокирован. \n");
    return 0;
}
